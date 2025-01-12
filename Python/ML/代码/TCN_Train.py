import os
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.model_selection import train_test_split
from sklearn.metrics import mean_squared_error, mean_absolute_error
import tensorflow as tf
from tensorflow import keras
from tensorflow.keras.layers import Conv1D, Dense, Flatten, Dropout  # 从 tensorflow.keras 导入层
from datetime import datetime  # 导入datetime模块

# 设置字体以防止中文显示乱码
from matplotlib import rcParams
rcParams['font.sans-serif'] = ['SimHei']
rcParams['axes.unicode_minus'] = False

def create_tcn_model(input_shape, num_filters=64, kernel_size=3, dropout_rate=0.2, learning_rate=0.001):
    """创建一个TCN模型。"""
    model = keras.Sequential([
        Conv1D(filters=num_filters, kernel_size=kernel_size, padding='causal', activation='relu', dilation_rate=1, input_shape=input_shape),
        Dropout(dropout_rate),
        Conv1D(filters=num_filters, kernel_size=kernel_size, padding='causal', activation='relu', dilation_rate=2),
        Dropout(dropout_rate),
        Conv1D(filters=num_filters, kernel_size=kernel_size, padding='causal', activation='relu', dilation_rate=4),
        Dropout(dropout_rate),
        Flatten(),
        Dense(1)
    ])
    optimizer = tf.keras.optimizers.Adam(learning_rate=learning_rate)  
    model.compile(optimizer=optimizer, loss='mse', metrics=['mae'])
    return model

def train_and_evaluate_tcn(file_path, epochs=20, batch_size=32, sequence_length=24):
    """训练和评估TCN模型。"""
    base_name = os.path.basename(file_path)
    region_name = os.path.splitext(base_name)[0]

    df = pd.read_csv(file_path)
    print(f"数据集列名：{df.columns}")

    if 'Datetime' not in df.columns:
        raise ValueError("'Datetime' 列在数据中不存在，请检查数据格式。")
    df['Datetime'] = pd.to_datetime(df['Datetime'])
    df.set_index('Datetime', inplace=True)

    target_column = None
    for col in df.columns:
        if 'MW' in col:
            target_column = col
            break
    if target_column is None:
        raise ValueError("未找到合适的目标列，请检查数据中的能源消耗列。")
    print(f"目标列：{target_column}")

    # 数据归一化
    from sklearn.preprocessing import MinMaxScaler  # 导入MinMaxScaler
    data = df[target_column].values.reshape(-1, 1)
    scaler = MinMaxScaler()
    data = scaler.fit_transform(data)

    def create_sequences(data, seq_length):
        xs = []
        ys = []
        for i in range(len(data) - seq_length - 1):
            x = data[i:(i + seq_length)]
            y = data[i + seq_length]
            xs.append(x)
            ys.append(y)
        return np.array(xs), np.array(ys)

    X, y = create_sequences(data, sequence_length)

    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, shuffle=False)

    input_shape = (X_train.shape[1], X_train.shape[2]) # 输入形状
    model = create_tcn_model(input_shape)

    # 记录训练开始时间
    start_time = datetime.now()
    print(f"训练开始时间：{start_time}")

    # 开始训练
    history = model.fit(X_train, y_train, epochs=epochs, batch_size=batch_size, validation_split=0.1)

    # 记录训练结束时间
    end_time = datetime.now()
    print(f"训练结束时间：{end_time}")

    # 计算训练时长
    training_duration = end_time - start_time
    print(f"训练时长：{training_duration}")

    y_pred = model.predict(X_test)

    # 反归一化
    y_test = scaler.inverse_transform(y_test)
    y_pred = scaler.inverse_transform(y_pred)

    mse = mean_squared_error(y_test, y_pred)
    rmse = np.sqrt(mse)
    mae = mean_absolute_error(y_test, y_pred)
    print(f"均方误差 (MSE): {mse:.2f}")
    print(f"均方根误差 (RMSE): {rmse:.2f}")
    print(f"平均绝对误差 (MAE): {mae:.2f}")

    # 可视化结果
    plt.figure(figsize=(12, 6))
    plt.plot(df.index[-len(y_test):], y_test, label=f'{region_name} 真实值', color='blue', linewidth=1) # 使用df的索引
    plt.plot(df.index[-len(y_test):], y_pred, label=f'{region_name} 预测值', color='red', linewidth=1) # 使用df的索引
    plt.title(f"{region_name} 能源消耗预测 (TCN)")
    plt.xlabel("时间")
    plt.ylabel(target_column)
    plt.legend()
    plt.grid()

    # 创建存储目录
    runs_dir = "runs"
    models_dir = os.path.join(runs_dir, "models")
    images_dir = os.path.join(runs_dir, "images")
    os.makedirs(runs_dir, exist_ok=True)
    os.makedirs(models_dir, exist_ok=True)
    os.makedirs(images_dir, exist_ok=True)

    # 保存预测结果图
    result_plot_file = os.path.join(images_dir, f"{region_name}_TCN_prediction_plot.png")
    plt.savefig(result_plot_file)
    plt.show()
    print(f"预测结果图已保存为：{result_plot_file}")

    # 保存训练好的模型
    model_file = os.path.join(models_dir, f"{region_name}_tcn_model.h5")
    model.save(model_file)  # 使用Keras的save方法保存模型
    print(f"模型已保存为：{model_file}")

# 主函数入口
if __name__ == "__main__":
    csv_file_path = "Data/AEP_hourly.csv"
    train_and_evaluate_tcn(csv_file_path)
