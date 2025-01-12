import argparse
import torch
from model.model import CatFaceModule
from model.data import CatPhotoDataModule
from pytorch_lightning import Trainer
from pytorch_lightning.loggers import TensorBoardLogger
from pytorch_lightning.callbacks import ModelCheckpoint
import os
import json

def main():
    # 解析命令行参数
    parser = argparse.ArgumentParser(description="Cat Recognize Model Trainer")
    parser.add_argument("--data", default="data/crop_photos", type=str, help="photo data directory (default: data/crop_photos)")
    parser.add_argument("--size", default=128, type=int, help="image size (default: 128)")
    parser.add_argument("--filter", default=2, type=int, help="cats whose number of photos is less than this value will be filtered (default: 10)")
    parser.add_argument("--balance", default=30, type=int, help="data sampling number of each cat in an epoch for balancing (default: 30)")
    parser.add_argument("--lr", default=3e-4, type=float, help="learning rate (default: 3e-4)")
    parser.add_argument("--batch", default=32, type=int, help="batch size (default: 32)")
    parser.add_argument("--epoch", default=100, type=int, help="number of epoches to run (default: 150)")
    parser.add_argument("--name", default='cat', type=str, help="model name (default: cat)")
    args = parser.parse_args()

    data_module = CatPhotoDataModule(args.data, args.size, args.filter, args.balance, args.batch, args.lr)

    # 手动调用 setup 方法
    data_module.setup(stage="fit")
    if data_module.cat_ids is None:
        raise ValueError("cat_ids is None after setup. Check data loading process.")

    model = CatFaceModule(num_classes=len(data_module.cat_ids), lr=args.lr) # 获取正确的类别数量

    # 判断 GPU 是否可用
    device = 'cuda' if torch.cuda.is_available() else 'cpu'
    print(f'training device: {device}')

    # 训练模型
    logger = TensorBoardLogger('./', version=args.name, default_hp_metric=False)
    checkpoint_callback = ModelCheckpoint(dirpath='checkpoints/', filename=args.name, monitor='val/acc', mode='max')
    trainer = Trainer(
        accelerator=device,
        devices=1 if device == 'gpu' else 1,
        logger=logger,
        callbacks=[checkpoint_callback],
        max_epochs=args.epoch
    )

    model.to(device)

    trainer.fit(model, datamodule=data_module)

    print('exporting model...')

    if not os.path.exists('export/'):
        os.mkdir('export/')

    # 加载最佳模型的checkpoint
    best_model_path = checkpoint_callback.best_model_path
    model = CatFaceModule.load_from_checkpoint(best_model_path)  # 加载最佳模型


    # 导出模型到 ONNX 文件, dummy_input 需要放在正确的设备上
    dummy_input = torch.randn(1, 3, args.size, args.size).to(model.device)
    model.to_onnx(f'export/{args.name}.onnx', dummy_input, export_params=True)

    # 保存模型使用的 cat id 映射顺序
    with open(f'export/{args.name}.json', 'w') as fp:
        json.dump(data_module.cat_ids, fp)

    print('done.')

if __name__ == '__main__':
    main()