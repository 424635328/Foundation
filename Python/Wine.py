import numpy as np
from sklearn.datasets import make_classification
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.metrics import accuracy_score

# 定义Adaline类
class Adaline:
    def __init__(self, eta=0.01, n_iter=50):
        """初始化Adaline算法的参数。
        eta: 学习率，控制权重更新的速度。
        n_iter: 训练时的最大迭代次数。
        """
        self.eta = eta
        self.n_iter = n_iter

    def fit(self, X, y):
        """训练模型。
        X: 特征矩阵。
        y: 目标值数组。
        """
        # 初始化权重，包括偏置项
        self.w_ = np.zeros(1 + X.shape[1])
        # 进行梯度下降
        for _ in range(self.n_iter):
            output = self.net_input(X)
            errors = y - output
            self.w_[1:] += self.eta * X.T.dot(errors)
            self.w_[0] += self.eta * errors.sum()

    def net_input(self, X):
        """计算模型的净输入。
        X: 单个样本的特征。
        """
        return np.dot(X, self.w_[1:]) + self.w_[0]

    def activation(self, X):
        """激活函数，用于二分类问题。
        X: 模型的输出。
        """
        return np.where(X >= 0.0, 1, -1)

    def predict(self, X):
        """预测新数据的类别。
        X: 特征矩阵。
        """
        return self.activation(self.net_input(X))

# 生成合成的二分类数据集
X, y = make_classification(n_samples=200, n_features=2, n_redundant=0, n_clusters_per_class=1)

# 划分训练集和测试集
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=42)

# 特征缩放
scaler = StandardScaler()
X_train = scaler.fit_transform(X_train)
X_test = scaler.transform(X_test)

# 创建Adaline实例并训练模型
ada = Adaline(eta=0.01, n_iter=50)
ada.fit(X_train, y_train)

# 预测测试集
y_pred = ada.predict(X_test)

# 计算准确率
accuracy = accuracy_score(y_test, y_pred)
print(f"Accuracy: {accuracy:.2f}")

