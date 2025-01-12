import torch
from torchvision.utils import save_image
import torchvision.transforms as transforms
from torch.utils.data import DataLoader
import os
from Test import Generator, VAE, CustomCelebADataset
from PIL import Image, ImageDraw, ImageFont
import numpy as np

# 检查是否有可用的GPU
device = torch.device("cuda" if torch.cuda.is_available() else "cpu")

# 数据预处理
transform = transforms.Compose([
    transforms.Resize(64),
    transforms.CenterCrop(64),
    transforms.ToTensor(),
    transforms.Normalize([0.5 for _ in range(3)], [0.5 for _ in range(3)])
])

# 加载数据集
image_folder_path = './Data/CelebA/img_align_celeba'
dataset = CustomCelebADataset(root_dir=image_folder_path, transform=transform)
dataloader = DataLoader(dataset, batch_size=16, shuffle=True, num_workers=0)

# 加载模型
nz = 100
gan_G = Generator(nz).to(device)
vae = VAE().to(device)

gan_G.load_state_dict(torch.load('gan_G.pth'))
vae.load_state_dict(torch.load('vae.pth'))

gan_G.eval()
vae.eval()

def add_text_to_image(image_tensor, text):
    # 将tensor转换为PIL图像
    image_np = (image_tensor.permute(1, 2, 0).cpu().numpy() * 0.5 + 0.5) * 255
    image_np = image_np.astype(np.uint8)
    image_pil = Image.fromarray(image_np)
    
    # 创建绘图对象
    draw = ImageDraw.Draw(image_pil)
    
    # 尝试加载中文字体，如果失败则依次尝试其他字体
    font = None
    font_size = 10
    try:
        # 尝试使用微软雅黑
        font = ImageFont.truetype("C:\\Windows\\Fonts\\msyh.ttc", font_size)
    except:
        try:
            # 尝试使用宋体
            font = ImageFont.truetype("C:\\Windows\\Fonts\\simsun.ttc", font_size)
        except:
            try:
                # 尝试使用黑体
                font = ImageFont.truetype("C:\\Windows\\Fonts\\simhei.ttf", font_size)
            except:
                font = ImageFont.load_default()
    
    # 计算文本大小
    if font:
        text_bbox = draw.textbbox((0, 0), text, font=font)
        text_width = text_bbox[2] - text_bbox[0]
        
        # 计算文本位置（居中）
        x = (64 - text_width) // 2
        y = 2
    else:
        x, y = 2, 2
    
    # 添加黑色背景框以提高可读性
    if font:
        text_height = text_bbox[3] - text_bbox[1]
        draw.rectangle([(x-2, y-2), (x+text_width+2, y+text_height+2)], fill='black')
    
    # 在图像顶部添加文字
    draw.text((x, y), text, fill=(255, 255, 255), font=font)
    
    # 转换回tensor
    image_tensor = transforms.ToTensor()(image_pil)
    image_tensor = (image_tensor * 2) - 1
    return image_tensor

# 生成图像并进行定性评估
with torch.no_grad():
    data = next(iter(dataloader))
    real_images = data.to(device)
    
    # GAN生成
    noise = torch.randn(16, nz, 1, 1, device=device)
    fake_gan = gan_G(noise)
    
    # VAE生成
    recon_vae, _, _ = vae(real_images)
    
    # 为每个图像添加标注
    labeled_real_images = torch.stack([add_text_to_image(img, "真实图像") for img in real_images.cpu()])
    labeled_fake_gan = torch.stack([add_text_to_image(img, "GAN生成") for img in fake_gan.cpu()])
    labeled_recon_vae = torch.stack([add_text_to_image(img, "VAE重建") for img in recon_vae.cpu()])
    
    # 保存对比图像
    comparison = torch.cat([labeled_real_images, labeled_fake_gan, labeled_recon_vae], dim=0)
    os.makedirs('qualitative_evaluation', exist_ok=True)
    save_image(comparison, "qualitative_evaluation/comparison_labeled.png", nrow=16, normalize=True, padding=2)

print("定性评估完成，带标注的生成图像与真实图像的比较已保存。")