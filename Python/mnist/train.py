import numpy as np
import pandas as pd

# 加载数据, 只将特征列指定为 np.float64
data = pd.read_csv("train.csv", header=0, dtype={'pixel0': np.float64, 'pixel1': np.float64,  'pixel783': np.float64}) # 将所有像素列名都列出来
test_data = pd.read_csv("test.csv", header=0, dtype={'pixel0': np.float64, 'pixel1': np.float64,  'pixel783': np.float64}) # 将所有像素列名都列出来

# 提取特征和标签
X = data.iloc[:, 1:].values / 255.0
y = data.iloc[:, 0].values.astype(int)  # 将标签转换为整数类型
X_test = test_data.iloc[:, :].values / 255.0

# 将标签转换为独热编码
y_onehot = np.zeros((y.shape[0], 10))
y_onehot[np.arange(y.shape[0]), y] = 1

# 手动实现 train_test_split
def train_test_split(X, y, test_size=0.2, random_state=None):
    if random_state is not None:
        np.random.seed(random_state)
    shuffled_indices = np.random.permutation(len(X))
    test_set_size = int(len(X) * test_size)
    test_indices = shuffled_indices[:test_set_size]
    train_indices = shuffled_indices[test_set_size:]
    return X[train_indices], X[test_indices], y[train_indices], y[test_indices]

# 划分训练集和验证集
X_train, X_val, y_train, y_val = train_test_split(X, y_onehot, test_size=0.2, random_state=42)

# 定义激活函数
def sigmoid(z):
    return 1 / (1 + np.exp(-z))

def softmax(z):
    exp_z = np.exp(z - np.max(z, axis=1, keepdims=True))
    return exp_z / np.sum(exp_z, axis=1, keepdims=True)

# 定义损失函数
def cross_entropy_loss(y, y_hat):
    return -np.sum(y * np.log(y_hat + 1e-10)) / y.shape[0]

# 定义神经网络类
class NeuralNetwork:
    def __init__(self, input_size, hidden_size, output_size):
        self.W1 = np.random.randn(input_size, hidden_size) * 0.01
        self.b1 = np.zeros((1, hidden_size))
        self.W2 = np.random.randn(hidden_size, output_size) * 0.01
        self.b2 = np.zeros((1, output_size))

    def forward(self, X):
        self.z1 = np.dot(X, self.W1) + self.b1
        self.a1 = sigmoid(self.z1)
        self.z2 = np.dot(self.a1, self.W2) + self.b2
        self.a2 = softmax(self.z2)
        return self.a2

    def backward(self, X, y, learning_rate):
        m = X.shape[0]

        dz2 = self.a2 - y
        dW2 = np.dot(self.a1.T, dz2) / m
        db2 = np.sum(dz2, axis=0, keepdims=True) / m

        dz1 = np.dot(dz2, self.W2.T) * self.a1 * (1 - self.a1)
        dW1 = np.dot(X.T, dz1) / m
        db1 = np.sum(dz1, axis=0, keepdims=True) / m

        self.W2 -= learning_rate * dW2
        self.b2 -= learning_rate * db2
        self.W1 -= learning_rate * dW1
        self.b1 -= learning_rate * db1

    def train(self, X_train, y_train, X_val, y_val, epochs, batch_size, learning_rate):
        for epoch in range(epochs):
            for i in range(0, X_train.shape[0], batch_size):
                X_batch = X_train[i:i + batch_size]
                y_batch = y_train[i:i + batch_size]

                y_hat = self.forward(X_batch)
                self.backward(X_batch, y_batch, learning_rate)

            y_train_pred = self.forward(X_train)
            train_loss = cross_entropy_loss(y_train, y_train_pred)
            train_acc = self.accuracy(y_train, y_train_pred)

            y_val_pred = self.forward(X_val)
            val_loss = cross_entropy_loss(y_val, y_val_pred)
            val_acc = self.accuracy(y_val, y_val_pred)

            print(
                f"Epoch {epoch + 1}/{epochs} - train_loss: {train_loss:.4f} - train_acc: {train_acc:.4f} - val_loss: {val_loss:.4f} - val_acc: {val_acc:.4f}")

    def predict(self, X):
        y_pred = self.forward(X)
        return np.argmax(y_pred, axis=1)

    def accuracy(self, y_true, y_pred):
        return np.mean(np.argmax(y_true, axis=1) == np.argmax(y_pred, axis=1))

# 手动实现评估指标
def accuracy_score(y_true, y_pred):
    return np.sum(y_true == y_pred) / len(y_true)

def precision_score(y_true, y_pred, average='macro'):
    if average == 'macro':
        precisions = []
        for c in range(10): # Assuming 10 classes (0-9)
            true_positives = np.sum((y_true == c) & (y_pred == c))
            false_positives = np.sum((y_true != c) & (y_pred == c))
            precision = true_positives / (true_positives + false_positives) if (true_positives + false_positives) > 0 else 0
            precisions.append(precision)
        return np.mean(precisions)

def recall_score(y_true, y_pred, average='macro'):
    if average == 'macro':
        recalls = []
        for c in range(10): # Assuming 10 classes (0-9)
            true_positives = np.sum((y_true == c) & (y_pred == c))
            false_negatives = np.sum((y_true == c) & (y_pred != c))
            recall = true_positives / (true_positives + false_negatives) if (true_positives + false_negatives) > 0 else 0
            recalls.append(recall)
        return np.mean(recalls)

def f1_score(y_true, y_pred, average='macro'):
    precision = precision_score(y_true, y_pred, average=average)
    recall = recall_score(y_true, y_pred, average=average)
    return 2 * (precision * recall) / (precision + recall) if (precision + recall) > 0 else 0
# 创建神经网络实例
input_size = 784
hidden_size = 128
output_size = 10
nn = NeuralNetwork(input_size, hidden_size, output_size)

# 训练模型
epochs = 30
batch_size = 64
learning_rate = 0.1
nn.train(X_train, y_train, X_val, y_val, epochs, batch_size, learning_rate)

# 使用验证集评估模型
y_val_pred = nn.predict(X_val)
y_val_true = np.argmax(y_val, axis=1)

# 计算评估指标
accuracy = accuracy_score(y_val_true, y_val_pred)
precision = precision_score(y_val_true, y_val_pred)
recall = recall_score(y_val_true, y_val_pred)
f1 = f1_score(y_val_true, y_val_pred)

# 打印结果
print(f"验证集准确率: {accuracy:.4f}")
print(f"验证集精确率: {precision:.4f}")
print(f"验证集召回率: {recall:.4f}")
print(f"验证集 F1 分数: {f1:.4f}")

# 使用测试集进行预测
predictions = nn.predict(X_test)

# 保存预测结果到文件
np.savetxt("predictions.csv", predictions, delimiter=",", fmt="%d")
print("预测结果已保存到 predictions.csv 文件中")