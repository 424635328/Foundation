import numpy as np

# 定义 sigmoid 激活函数
def sigmoid(x): 
  return 1 / (1 + np.exp(-x)) 

# 定义 sigmoid 函数的导数，用于反向传播时计算误差
def sigmoid_derivative(x):
  return x * (1 - x) 

# 输入数据，表示 XOR 逻辑的四种输入情况
X = np.array([[0, 0], 
              [0, 1],
              [1, 0],
              [1, 1]])

# 目标输出，表示 XOR 逻辑对应的四种输出结果
y = np.array([[0],
              [1],
              [1],
              [0]])

# 初始化权重，相当于随机设置神经网络中每个连接的强度
# 2个输入节点到 3个隐藏层节点的连接权重(matrix)
hidden_weights = np.random.uniform(size=(2, 3)) 
# 3个隐藏层节点到 1个输出节点的连接权重
output_weights = np.random.uniform(size=(3, 1)) 

# 初始化学习率
learning_rate = 0.5

# 学习率衰减因子
decay_rate = 0.9999

# 训练循环，循环 10000 次，每次循环都会调整权重，使预测结果更接近目标输出
for epoch in range(10000):
  # 前向传播，根据输入数据和权重计算预测结果
  # 计算隐藏层的输入
  hidden_layer_input = np.dot(X, hidden_weights) 
  # 计算隐藏层的输出
  hidden_layer_output = sigmoid(hidden_layer_input) 
  # 计算输出层的输入
  output_layer_input = np.dot(hidden_layer_output, output_weights) 
  # 计算输出层的输出
  output_layer_output = sigmoid(output_layer_input) 

  # 计算误差，即预测结果与目标输出之间的差距
  error = y - output_layer_output 

  # 反向传播，根据误差调整权重
  # 计算输出层的梯度
  d_output = error * sigmoid_derivative(output_layer_output) 
  # 计算隐藏层的梯度
  error_hidden_layer = d_output.dot(output_weights.T) 
  d_hidden_layer = error_hidden_layer * sigmoid_derivative(hidden_layer_output) 

  # 更新权重，根据梯度调整连接强度
  output_weights += hidden_layer_output.T.dot(d_output) * learning_rate 
  hidden_weights += X.T.dot(d_hidden_layer) * learning_rate 

  # 动态调整学习率
  learning_rate = learning_rate * decay_rate

# 测试训练后的模型，使用训练好的模型对输入数据进行预测
# 计算隐藏层的输入
hidden_layer_input = np.dot(X, hidden_weights) 
# 计算隐藏层的输出
hidden_layer_output = sigmoid(hidden_layer_input) 
# 计算输出层的输入
output_layer_input = np.dot(hidden_layer_output, output_weights) 
# 计算输出层的输出
output_layer_output = sigmoid(output_layer_input) 

# 打印预测结果
print("预测结果:")
print(output_layer_output) 