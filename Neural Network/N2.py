import numpy as np

# 激活函数：Sigmoid
def sigmoid(x):
    return 1 / (1 + np.exp(-x))

# Sigmoid函数的导数
def sigmoid_derivative(x):
    return x * (1 - x)

# 初始化数据
np.random.seed(42)
X = np.random.rand(100, 2)  # 100个样本，每个样本有2个特征
y = np.random.randint(0, 2, (100, 1))  # 100个样本的标签（0或1）

# 初始化权重和偏置
input_layer_neurons = X.shape[1]  # 输入层神经元数
hidden_layer_neurons = 4  # 隐藏层神经元数
output_neurons = 1  # 输出层神经元数

# 权重和偏置初始化
wh = np.random.uniform(size=(input_layer_neurons, hidden_layer_neurons))
bh = np.random.uniform(size=(1, hidden_layer_neurons))
wo = np.random.uniform(size=(hidden_layer_neurons, output_neurons))
bo = np.random.uniform(size=(1, output_neurons))

# 设置学习率和训练次数
learning_rate = 0.1
epochs = 10000

# 训练神经网络
for epoch in range(epochs):
    # 前向传播
    hidden_layer_input = np.dot(X, wh) + bh
    hidden_layer_activation = sigmoid(hidden_layer_input)
    output_layer_input = np.dot(hidden_layer_activation, wo) + bo
    predicted_output = sigmoid(output_layer_input)
    
    # 计算误差
    error = y - predicted_output
    
    # 反向传播
    d_predicted_output = error * sigmoid_derivative(predicted_output)
    error_hidden_layer = d_predicted_output.dot(wo.T)
    d_hidden_layer = error_hidden_layer * sigmoid_derivative(hidden_layer_activation)
    
    # 更新权重和偏置
    wo += hidden_layer_activation.T.dot(d_predicted_output) * learning_rate
    bo += np.sum(d_predicted_output, axis=0, keepdims=True) * learning_rate
    wh += X.T.dot(d_hidden_layer) * learning_rate
    bh += np.sum(d_hidden_layer, axis=0, keepdims=True) * learning_rate

print("训练完成后的输出：")
print(predicted_output)
