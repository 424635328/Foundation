# data.py
from typing import List, Tuple

import os
import math
import random
import torch
import pyarrow as pa
import numpy as np
from PIL import Image
from torch import Tensor
from torchvision import transforms
from torch.utils.data import Dataset, DataLoader
from pytorch_lightning import LightningDataModule
from torchvision.transforms import RandAugment, ToTensor, Normalize
from model.model import CatFaceModule


class CatPhotoDataset(Dataset):
    """
    猫图片数据集类。

    Args:
        data (List[List[str]]): 包含每个类别图片路径的列表。
        size (int): 图片大小。
        num_classes (int): 类别数量。
        balance_num (int): 每个epoch中每个类别的采样数量。
        augmentation (bool): 是否进行数据增强。
    """
    def __init__(self, data: List[List[str]], size: int, num_classes: int, balance_num: int, augmentation: bool = False):
        self.data = pa.array(data)  # 使用pyarrow避免pytorch dataloader worker多份拷贝
        self.size = size
        self.num_classes = num_classes
        self.balance_num = balance_num

        if augmentation:
            self.transform = transforms.Compose([
                transforms.RandomResizedCrop(size, scale=(0.8, 1.0)),  # 随机裁剪和缩放
                transforms.RandomHorizontalFlip(p=0.5),  # 随机水平翻转
                transforms.RandomVerticalFlip(p=0.5),  # 随机垂直翻转
                transforms.RandomRotation(degrees=15, fill=0),  # 随机旋转
                transforms.ColorJitter(brightness=0.1, contrast=0.1, saturation=0.1),  # 随机颜色抖动
                RandAugment(num_ops=2, magnitude=9),  # RandAugment数据增强
                transforms.ToTensor(),  # 转换为Tensor
                transforms.Normalize(mean=[0.485, 0.456, 0.406], std=[0.229, 0.224, 0.225])  # 标准化
            ])
        else:
            self.transform = transforms.Compose([
                transforms.Resize((size, size)),  # 调整大小
                transforms.ToTensor(),  # 转换为Tensor
                transforms.Normalize(mean=[0.485, 0.456, 0.406], std=[0.229, 0.224, 0.225])  # 标准化
            ])

    def __len__(self) -> int:
        return self.num_classes * self.balance_num

    def __getitem__(self, index: int) -> Tuple[Tensor, int]:
        class_idx = index // self.balance_num
        class_data = self.data[class_idx].as_py()

        while True:
            try:
                img_path = random.choice(class_data)
                img = Image.open(img_path).convert('RGB')
                break
            except Exception as e:
                print(f"Error opening image {img_path}: {e}")
                continue

        if self.transform:
            img = self.transform(img)
        else:
            img = ToTensor()(img)
            img = Normalize(mean=[0.485, 0.456, 0.406], std=[0.229, 0.224, 0.225])(img)

        return img, class_idx


class CatPhotoDataModule(LightningDataModule):
    """
    猫图片数据模块类。

    Args:
        root (str): 数据集根目录。
        size (int): 图片大小。
        filter_num (int): 图片数量少于此值的类别将被过滤。
        balance_num (int): 每个epoch中每个类别的采样数量。
        batch_size (int): 批次大小。
    """
    def __init__(self, root, size, filter_num, balance_num, batch_size, lr):  # 添加 lr 参数
        super().__init__()
        self.save_hyperparameters()  # 现在会保存 lr

    def setup(self, stage=None):
        cat_photos = {}
        for dir_name in os.listdir(self.hparams['root']):
            dir_path = os.path.join(self.hparams['root'], dir_name)
            if os.path.isdir(dir_path):
                cat_photos[dir_name] = []
                for file_name in os.listdir(dir_path):
                    file_path = os.path.join(dir_path, file_name)
                    cat_photos[dir_name].append(file_path)
                cat_photos[dir_name].sort()

        cat_ids = list(cat_photos.keys())
        print(f'total number of cats: {len(cat_ids)}')

        cat_with_enough_photo_ids = [cat_id for cat_id in cat_ids if len(cat_photos[cat_id]) >= self.hparams['filter_num']]
        cat_with_enough_photo_ids.sort()
        print(f'number of cats with enough photos: {len(cat_with_enough_photo_ids)}, other cats would be ignored')
        self.cat_ids = cat_with_enough_photo_ids

        train_data = [[] for _ in self.cat_ids] # 修改为列表的列表
        val_data = [[] for _ in self.cat_ids]

        for cat_idx, cat_id in enumerate(self.cat_ids):
            photos = cat_photos[cat_id]
            num_photos = len(photos)
            num_train = math.floor(num_photos * 0.8)
            train_data[cat_idx] = photos[:num_train]
            val_data[cat_idx] = photos[num_train:]

        train_augmentation = stage == "fit" or stage is None
        val_augmentation = False

        self.train_dataset = CatPhotoDataset(train_data, self.hparams['size'], len(self.cat_ids), self.hparams['balance_num'], augmentation=train_augmentation)
        self.val_dataset = CatPhotoDataset(val_data, self.hparams['size'], len(self.cat_ids), math.ceil(self.hparams['balance_num'] * 0.2), augmentation=val_augmentation)

        if stage == "fit" or stage is None: # 只在训练阶段创建模型
            self.model = CatFaceModule(num_classes=len(self.cat_ids), lr=self.hparams.lr) # 在 setup 中初始化模型
        self.class_weights = self.calculate_class_weights(stage) # 在 setup 中计算类别权重


    def calculate_class_weights(self, stage):
        """计算类别权重，用于处理类别不平衡问题."""
        if stage != "fit" and stage is not None: # 仅在 fit 阶段计算权重
            return None

        class_counts = [len(data) for data in self.train_dataset.data.to_pylist()]
        total_samples = sum(class_counts)

        if total_samples == 0:
            print("Warning: No training samples found. Using uniform class weights.")
            return torch.ones(len(class_counts)) # 不指定设备

        class_weights = [total_samples / (len(class_counts) * (count if count > 0 else 1)) for count in class_counts]
        return torch.Tensor(class_weights) # 不指定设备


    def train_dataloader(self) -> DataLoader:
        """创建训练数据加载器."""
        return DataLoader(self.train_dataset, batch_size=self.hparams['batch_size'], shuffle=True, num_workers=4, persistent_workers=True)

    def val_dataloader(self) -> DataLoader:
        """创建验证数据加载器."""
        return DataLoader(self.val_dataset, batch_size=self.hparams['batch_size'], shuffle=False, num_workers=4, persistent_workers=True)