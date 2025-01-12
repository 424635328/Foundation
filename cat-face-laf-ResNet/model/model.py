# model.py
import torch
import torch.nn as nn
from torchvision import models
import torch.optim as optim
from pytorch_lightning import LightningModule
import torchmetrics
from typing import Tuple, List

class CatFaceModule(LightningModule):
    """
    猫脸识别模型类。

    Args:
        num_classes (int): 类别数量。
        lr (float): 学习率。
        weight_decay (float): 权重衰减。
    """
    def __init__(self, num_classes: int, lr: float = 1e-4, weight_decay: float = 1e-5):
        super().__init__()
        self.save_hyperparameters()

        self.net = models.resnet50(pretrained=True)
        num_ftrs = self.net.fc.in_features
        self.net.fc = nn.Linear(num_ftrs, num_classes)


    def forward(self, x: torch.Tensor) -> torch.Tensor:
        """前向传播."""
        return self.net(x)

    def training_step(self, batch: Tuple[torch.Tensor, torch.LongTensor], batch_idx: int) -> torch.Tensor:
        """训练步骤."""
        loss, acc = self.do_step(batch)
        self.log('train/loss', loss, on_step=True, on_epoch=True)
        self.log('train/acc', acc, on_step=True, on_epoch=True)
        return loss

    def validation_step(self, batch: Tuple[torch.Tensor, torch.LongTensor], batch_idx: int):
        """验证步骤."""
        loss, acc = self.do_step(batch)
        self.log('val/loss', loss, on_step=False, on_epoch=True)
        self.log('val/acc', acc, on_step=False, on_epoch=True) # 添加 acc 参数

    def do_step(self, batch: Tuple[torch.Tensor, torch.LongTensor]) -> Tuple[torch.Tensor, torch.Tensor]:
        x, y = batch
        out = self.net(x)

        if self.trainer.datamodule.class_weights is not None: # 检查 class_weights 是否为 None
            class_weights = self.trainer.datamodule.class_weights.to(self.device) # 将权重移动到当前设备
            loss = nn.CrossEntropyLoss(weight=class_weights)(out, y)
        else:
            loss = nn.CrossEntropyLoss()(out, y) # 如果 class_weights 为 None，则不使用权重

        with torch.no_grad():
            accuracy_per_class = torchmetrics.functional.accuracy(out, y, task="multiclass", num_classes=self.hparams['num_classes'], average=None)
            nan_mask = accuracy_per_class.isnan()
            accuracy_per_class = accuracy_per_class.masked_fill(nan_mask, 0)
            acc = accuracy_per_class.sum() / (~nan_mask).sum()

        return loss, acc


    def configure_optimizers(self) -> optim.Optimizer:
        """配置优化器."""
        optimizer = optim.AdamW(self.parameters(), lr=self.hparams.lr, weight_decay=self.hparams.weight_decay)
        scheduler = optim.lr_scheduler.ReduceLROnPlateau(optimizer, mode="min", factor=0.1, patience=3)
        return {
            "optimizer": optimizer,
            "lr_scheduler": scheduler,
            "monitor": "val/loss"  # 监控验证损失以调整学习率
        }