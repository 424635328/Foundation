import tensorflow as tf
import numpy as np

# 加载 MNIST 数据集
(x_train, y_train), (x_test, y_test) = tf.keras.datasets.mnist.load_data()

# 数据预处理
# 将图像数据从 0-255 归一化到 0-1
x_train = x_train.astype('float32') / 255
x_test = x_test.astype('float32') / 255

# 将标签数据转换为 one-hot 编码
y_train = tf.keras.utils.to_categorical(y_train, num_classes=10)
y_test = tf.keras.utils.to_categorical(y_test, num_classes=10)

# 定义模型
model = tf.keras.models.Sequential([
  tf.keras.layers.Flatten(input_shape=(28, 28)), # 将图像展平成一维向量
  tf.keras.layers.Dense(128, activation='relu'), # 隐藏层，128 个神经元，ReLU 激活函数
  tf.keras.layers.Dense(10, activation='softmax') # 输出层，10 个神经元，Softmax 激活函数
])

# 编译模型
model.compile(optimizer='adam', # 使用 Adam 优化器
              loss='categorical_crossentropy', # 使用交叉熵损失函数
              metrics=['accuracy']) # 使用准确率评估模型

# 训练模型
model.fit(x_train, y_train, epochs=10, batch_size=32) # 训练 10 个 epoch，每个 batch 包含 32 个样本

# 评估模型
loss, accuracy = model.evaluate(x_test, y_test)
print(f"Test loss: {loss}")
print(f"Test accuracy: {accuracy}")