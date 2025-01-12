# 导入必要的库
import os
import torch
import torchvision
from torchvision import transforms
from torch.utils.data import DataLoader
from torchvision.datasets import ImageFolder
from torchvision.utils import save_image
import torch.nn as nn
import torch.optim as optim
from skimage.metrics import peak_signal_noise_ratio as psnr
from skimage.metrics import structural_similarity as ssim
import numpy as np
from PIL import Image
from tqdm import tqdm
import matplotlib.pyplot as plt
import torchvision.utils as vutils
from torch.utils.data import Dataset

# 检查是否有可用的GPU
device = torch.device("cuda" if torch.cuda.is_available() else "cpu")

# 数据预处理
transform = transforms.Compose([
    transforms.Resize(64),
    transforms.CenterCrop(64),
    transforms.ToTensor(),
    transforms.Normalize([0.5 for _ in range(3)], [0.5 for _ in range(3)])
])

# 自定义数据集类
class CustomCelebADataset(Dataset):
    def __init__(self, root_dir, transform=None):
        self.root_dir = root_dir
        self.transform = transform
        self.image_files = [f for f in os.listdir(root_dir) if f.endswith('.jpg')]

    def __len__(self):
        return len(self.image_files)

    def __getitem__(self, idx):
        img_name = os.path.join(self.root_dir, self.image_files[idx])
        image = Image.open(img_name)
        if self.transform:
            image = self.transform(image)
        return image

# 定义GAN生成器
class Generator(nn.Module):
    def __init__(self, nz=100, ngf=64, nc=3):
        super(Generator, self).__init__()
        self.main = nn.Sequential(
            nn.ConvTranspose2d(nz, ngf * 8, 4, 1, 0, bias=False),
            nn.BatchNorm2d(ngf * 8),
            nn.ReLU(True),
            nn.ConvTranspose2d(ngf * 8, ngf * 4, 4, 2, 1, bias=False),
            nn.BatchNorm2d(ngf * 4),
            nn.ReLU(True),
            nn.ConvTranspose2d(ngf * 4, ngf * 2, 4, 2, 1, bias=False),
            nn.BatchNorm2d(ngf * 2),
            nn.ReLU(True),
            nn.ConvTranspose2d(ngf * 2, ngf, 4, 2, 1, bias=False),
            nn.BatchNorm2d(ngf),
            nn.ReLU(True),
            nn.ConvTranspose2d(ngf, nc, 4, 2, 1, bias=False),
            nn.Tanh()
        )
    
    def forward(self, input):
        return self.main(input)

# 定义GAN判别器
class Discriminator(nn.Module):
    def __init__(self, nc=3, ndf=64):
        super(Discriminator, self).__init__()
        self.main = nn.Sequential(
            nn.Conv2d(nc, ndf, 4, 2, 1, bias=False),
            nn.LeakyReLU(0.2, inplace=True),
            nn.Conv2d(ndf, ndf * 2, 4, 2, 1, bias=False),
            nn.BatchNorm2d(ndf * 2),
            nn.LeakyReLU(0.2, inplace=True),
            nn.Conv2d(ndf * 2, ndf * 4, 4, 2, 1, bias=False),
            nn.BatchNorm2d(ndf * 4),
            nn.LeakyReLU(0.2, inplace=True),
            nn.Conv2d(ndf * 4, ndf * 8, 4, 2, 1, bias=False),
            nn.BatchNorm2d(ndf * 8),
            nn.LeakyReLU(0.2, inplace=True),
            nn.Conv2d(ndf * 8, 1, 4, 1, 0, bias=False),
            nn.Sigmoid()
        )
    
    def forward(self, input):
        return self.main(input).view(-1)

# 定义VAE编码器
class VAE_Encoder(nn.Module):
    def __init__(self, input_channels=3, latent_dim=100):
        super(VAE_Encoder, self).__init__()
        self.conv = nn.Sequential(
            nn.Conv2d(input_channels, 32, 4, 2, 1),
            nn.ReLU(),
            nn.Conv2d(32, 64, 4, 2, 1),
            nn.ReLU(),
            nn.Conv2d(64, 128, 4, 2, 1),
            nn.ReLU(),
            nn.Conv2d(128, 256, 4, 2, 1),
            nn.ReLU()
        )
        self.fc_mu = nn.Linear(256*4*4, latent_dim)
        self.fc_logvar = nn.Linear(256*4*4, latent_dim)
    
    def forward(self, x):
        x = self.conv(x)
        x = x.view(x.size(0), -1)
        mu = self.fc_mu(x)
        logvar = self.fc_logvar(x)
        return mu, logvar

# 定义VAE解码器
class VAE_Decoder(nn.Module):
    def __init__(self, latent_dim=100, output_channels=3):
        super(VAE_Decoder, self).__init__()
        self.fc = nn.Linear(latent_dim, 256*4*4)
        self.deconv = nn.Sequential(
            nn.ConvTranspose2d(256, 128, 4, 2, 1),
            nn.ReLU(),
            nn.ConvTranspose2d(128, 64, 4, 2, 1),
            nn.ReLU(),
            nn.ConvTranspose2d(64, 32, 4, 2, 1),
            nn.ReLU(),
            nn.ConvTranspose2d(32, output_channels, 4, 2, 1),
            nn.Tanh()
        )
    
    def forward(self, z):
        z = self.fc(z)
        z = z.view(z.size(0), 256, 4, 4)
        z = self.deconv(z)
        return z

# 定义VAE模型
class VAE(nn.Module):
    def __init__(self, input_channels=3, latent_dim=100):
        super(VAE, self).__init__()
        self.encoder = VAE_Encoder(input_channels, latent_dim)
        self.decoder = VAE_Decoder(latent_dim, input_channels)
    
    def reparameterize(self, mu, logvar):
        std = torch.exp(0.5 * logvar)
        eps = torch.randn_like(std)
        return mu + eps * std
    
    def forward(self, x):
        mu, logvar = self.encoder(x)
        z = self.reparameterize(mu, logvar)
        recon = self.decoder(z)
        return recon, mu, logvar

# 初始化模型
nz = 100
gan_G = Generator(nz).to(device)
gan_D = Discriminator().to(device)
vae = VAE().to(device)

# 初始化权重
def weights_init(m):
    classname = m.__class__.__name__
    if classname.find('Conv') != -1:
        nn.init.normal_(m.weight.data, 0.0, 0.02)
    elif classname.find('BatchNorm') != -1:
        nn.init.normal_(m.weight.data, 1.0, 0.02)
        nn.init.constant_(m.bias.data, 0)

gan_G.apply(weights_init)
gan_D.apply(weights_init)
vae.apply(weights_init)

# 定义损失函数
criterion = nn.BCELoss()
reconstruction_loss = nn.MSELoss()
kld_loss = lambda mu, logvar: -0.5 * torch.sum(1 + logvar - mu.pow(2) - logvar.exp())

# 定义优化器
optimizer_G = optim.Adam(gan_G.parameters(), lr=0.0002, betas=(0.5, 0.999))
optimizer_D = optim.Adam(gan_D.parameters(), lr=0.0002, betas=(0.5, 0.999))
optimizer_vae = optim.Adam(vae.parameters(), lr=0.001)

# 训练GAN
def train_gan(epoch):
    gan_G.train()
    gan_D.train()
    for i, data in enumerate(tqdm(dataloader, desc=f"GAN Training Epoch {epoch}"), 0):
        real_images = data.to(device)
        if real_images.dim() == 3:
            real_images = real_images.unsqueeze(0)

        b_size = real_images.size(0)
        label = torch.full((b_size,), 1., dtype=torch.float, device=device)

        # 训练判别器
        gan_D.zero_grad()
        output = gan_D(real_images)
        loss_D_real = criterion(output, label)
        loss_D_real.backward()

        noise = torch.randn(b_size, nz, 1, 1, device=device)
        fake = gan_G(noise)
        label.fill_(0.)
        output = gan_D(fake.detach())
        loss_D_fake = criterion(output, label)
        loss_D_fake.backward()
        loss_D = loss_D_real + loss_D_fake
        optimizer_D.step()

        # 训练生成器
        gan_G.zero_grad()
        label.fill_(1.)
        output = gan_D(fake)
        loss_G = criterion(output, label)
        loss_G.backward()
        optimizer_G.step()

        if i % 100 == 0:
            tqdm.write(f"[GAN][{epoch}][{i}/{len(dataloader)}] Loss_D: {loss_D.item():.4f} Loss_G: {loss_G.item():.4f}")

    # 保存生成的图片
    with torch.no_grad():
        fake = gan_G(noise).detach().cpu()
    save_image(fake, f"gan_images/epoch_{epoch}.png", normalize=True)

# 训练VAE
def train_vae(epoch):
    vae.train()
    total_loss = 0
    for i, data in enumerate(tqdm(dataloader, desc=f"VAE Training Epoch {epoch}"), 0):
        real_images = data.to(device)
        optimizer_vae.zero_grad()
        recon, mu, logvar = vae(real_images)
        loss_recon = reconstruction_loss(recon, real_images)
        loss_kld = kld_loss(mu, logvar)
        loss = loss_recon + loss_kld
        loss.backward()
        total_loss += loss.item()
        optimizer_vae.step()

        if i % 100 == 0:
            tqdm.write(f"[VAE][{epoch}][{i}/{len(dataloader)}] Loss: {loss.item():.4f}")

    avg_loss = total_loss / len(dataloader)
    print(f"[VAE][{epoch}] Average Loss: {avg_loss:.4f}")
    # 保存重建的图片
    with torch.no_grad():
        recon, _, _ = vae(real_images)
    save_image(recon, f"vae_images/epoch_{epoch}.png", normalize=True)

# 评估模型
def evaluate():
    vae.eval()
    gan_G.eval()
    with torch.no_grad():
        data = next(iter(dataloader))
        real_images = data.to(device)[:16]
        
        noise = torch.randn(16, nz, 1, 1, device=device)
        fake_gan = gan_G(noise)
        
        recon_vae, _, _ = vae(real_images)
        
        real = real_images.cpu().numpy()
        gan_generated = fake_gan.cpu().numpy()
        vae_generated = recon_vae.cpu().numpy()
        
        psnr_gan = []
        ssim_gan = []
        psnr_vae = []
        ssim_vae = []
        for i in range(real.shape[0]):
            real_img = np.transpose((real[i] * 0.5 + 0.5), (1, 2, 0))
            gan_img = np.transpose((gan_generated[i] * 0.5 + 0.5), (1, 2, 0))
            vae_img = np.transpose((vae_generated[i] * 0.5 + 0.5), (1, 2, 0))
            
            # 检查图像尺寸
            print(f"Real image size: {real_img.shape}, GAN image size: {gan_img.shape}, VAE image size: {vae_img.shape}")
            
            psnr_gan.append(psnr(real_img, gan_img, data_range=1.0))
            ssim_gan.append(ssim(real_img, gan_img, multichannel=True, win_size=3, data_range=1.0))
            
            psnr_vae.append(psnr(real_img, vae_img, data_range=1.0))
            ssim_vae.append(ssim(real_img, vae_img, multichannel=True, win_size=3, data_range=1.0))
        
        avg_psnr_gan = np.mean(psnr_gan)
        avg_ssim_gan = np.mean(ssim_gan)
        avg_psnr_vae = np.mean(psnr_vae)
        avg_ssim_vae = np.mean(ssim_vae)
        
        print(f"GAN - 平均PSNR: {avg_psnr_gan:.2f}, 平均SSIM: {avg_ssim_gan:.4f}")
        print(f"VAE - 平均PSNR: {avg_psnr_vae:.2f}, 平均SSIM: {avg_ssim_vae:.4f}")
        
        comparison = torch.cat([real_images[:16], fake_gan[:16], recon_vae[:16]])
        save_image(comparison, "evaluation/comparison.png", nrow=16, normalize=True)

# 主函数
if __name__ == '__main__':
    # 创建必要的目录
    os.makedirs("gan_images", exist_ok=True)
    os.makedirs("vae_images", exist_ok=True)
    os.makedirs("evaluation", exist_ok=True)

    # 加载数据集
    image_folder_path = './Data/CelebA/img_align_celeba'
    dataset = CustomCelebADataset(root_dir=image_folder_path, transform=transform)
    dataloader = DataLoader(dataset, batch_size=256, shuffle=True, num_workers=0)  # 将 num_workers 设置为 0

    # 验证数据集加载
    dataiter = iter(dataloader)
    images = next(dataiter)

    # 显示图像
    grid = vutils.make_grid(images[:16], nrow=4, normalize=True)
    npimg = grid.numpy()
    plt.imshow(np.transpose(npimg, (1, 2, 0)))
    plt.axis('off')  # 关闭坐标轴
    plt.show()

    # 训练和评估模型
    num_epochs = 15
    for epoch in range(1, num_epochs + 1):
        train_gan(epoch)
        train_vae(epoch)

    # 评估模型
    evaluate()
    # 输出结论
    print("评估完成，生成图像与真实图像的比较已完成。")
    torch.save(gan_G.state_dict(), 'gan_G.pth')
    torch.save(gan_D.state_dict(), 'gan_D.pth')
    torch.save(vae.state_dict(), 'vae.pth')
    print("模型已保存。")
