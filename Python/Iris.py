import numpy as np
import matplotlib.pyplot as plt
from sklearn.datasets import load_iris
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score

class Adaline:
    def __init__(self, eta=0.001, iter_num=500, batch_size=1):
        """初始化Adaline算法的参数。
        eta: 学习率，控制权重更新的速度。
        iter_num: 训练时的最大迭代次数。
        batch_size: 梯度下降的批量大小，1表示随机梯度下降。
        """
        self.eta = eta
        self.iter_num = iter_num
        self.batch_size = batch_size

    def train(self, X, Y):
        """训练模型。
        X: 特征矩阵。
        Y: 目标值数组。
        """
        self.w = np.zeros(1 + X.shape[1])  # 初始化权重，包括偏置项
        self.l = np.zeros(self.iter_num)  # 初始化损失记录数组

        for iter_index in range(self.iter_num):
            errors = []  # 存储每个样本的误差
            for sample_index in range(X.shape[0]):
                x_i = X[sample_index]  # 获取单个样本的特征
                y_i = Y[sample_index]  # 获取单个样本的目标值
                output = self.net_input(x_i)  # 计算模型输出
                error = y_i - self.activation(output)  # 计算误差
                errors.append(error)
                self.w[0] += self.eta * error  # 更新偏置项
                self.w[1:] += self.eta * error * x_i  # 更新权重

            self.l[iter_index] = np.mean(np.array(errors) ** 2) / 2.0  # 计算平均损失
            if iter_index > 0 and np.abs(self.l[iter_index - 1] - self.l[iter_index]) < 0.0001:
                break  # 如果损失变化很小，则提前停止训练

    def activation(self, x):
        """激活函数，用于二分类问题。
        x: 模型的输出。
        """
        return np.where(x >= 0.0, 1, -1)

    def net_input(self, x):
        """计算模型的净输入。
        x: 单个样本的特征。
        """
        return np.dot(x, self.w[1:]) + self.w[0]

    def predict(self, X):
        """预测新数据的类别。
        X: 特征矩阵。
        """
        return self.activation(self.net_input(X))

def main():
    iris = load_iris()  # 加载鸢尾花数据集
    features = iris.data[:99, [0, 2]]  # 提取前两个特征
    labels = np.where(iris.target[:99] == 0, -1, 1)  # 将标签转换为-1和1

    # 特征缩放
    features_std = np.copy(features)
    for i in range(features.shape[1]):
        features_std[:, i] = (features_std[:, i] - features[:, i].mean()) / features[:, i].std()

    # 划分训练集和测试集
    train_features, test_features, train_labels, test_labels = train_test_split(
        features_std, labels, test_size=0.33, random_state=23323)

    classifier = Adaline()  # 创建Adaline实例
    classifier.train(train_features, train_labels)  # 训练模型

    test_predict = classifier.predict(test_features)  # 预测测试集
    score = accuracy_score(test_labels, test_predict)  # 计算准确率
    print("The accuracy score is: %s" % score)  # 打印准确率

    # 绘制决策边界
    x_min, x_max = train_features[:, 0].min() - 1, train_features[:, 0].max() + 1
    y_min, y_max = train_features[:, 1].min() - 1, train_features[:, 1].max() + 1
    plt.xlim(x_min, x_max)
    plt.ylim(y_min, y_max)
    plt.xlabel("sepal length [standardized]")
    plt.ylabel("petal length [standardized]")
    plt.scatter(train_features[:, 0], train_features[:, 1], c=train_labels, marker='o', s=10)
    k = -classifier.w[1] / classifier.w[2]
    d = -classifier.w[0] / classifier.w[2]
    plt.plot([x_min, x_max], [k * x_min + d, k * x_max + d], "go-")
    plt.show()  # 显示图形

if __name__ == "__main__":
    main()