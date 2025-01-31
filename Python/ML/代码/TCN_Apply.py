
import os
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.metrics import mean_squared_error, mean_absolute_error
from sklearn.preprocessing import MinMaxScaler
from tensorflow.keras.models import load_model
from tensorflow.keras import losses
from datetime import datetime

# 设置字体以防止中文乱码
from matplotlib import rcParams
rcParams['font.sans-serif'] = ['SimHei']
rcParams['axes.unicode_minus'] = False

def apply_model(file_path, model_path, sequence_length=24):
    """
    加载已训练的TCN模型，对整个数据集进行预测，并评估模型。
    """
    # 从文件路径中提取地区名称
    base_name = os.path.basename(file_path)
    region_name = os.path.splitext(base_name)[0]

    # 加载数据
    print(f"加载数据文件：{file_path}")
    df = pd.read_csv(file_path)

    # 检查列名，确保存在目标列
    print(f"数据集列名：{df.columns}")

    # 确保 'Datetime' 列存在并处理时间格式
    if 'Datetime' not in df.columns:
        raise ValueError("'Datetime' 列在数据中不存在，请检查数据格式。")
    df['Datetime'] = pd.to_datetime(df['Datetime'])
    df.set_index('Datetime', inplace=True)

    # 动态识别目标列（以 'MW' 或 'Consumption' 结尾）
    target_column = None
    for col in df.columns:
        if 'MW' in col or 'Consumption' in col:
            target_column = col
            break

    if target_column is None:
        raise ValueError("未找到合适的目标列，请检查数据中的能源消耗列。")

    print(f"目标列：{target_column}")

    # 数据归一化
    data = df[target_column].values.reshape(-1, 1)
    scaler = MinMaxScaler()
    data = scaler.fit_transform(data)

    # 创建时间序列数据
    def create_sequences(data, seq_length):
        # 初始化两个空列表，用于存储输入序列和目标值
        xs = []
        ys = []
        # 遍历数据，生成序列
        # 注意这里循环的终止条件是 len(data) - seq_length - 1
        # 这样可以确保每个序列都有足够的长度，并且每个序列后面都有一个目标值
        for i in range(len(data) - seq_length - 1):
            # 从数据中提取长度为 seq_length 的序列作为输入
            x = data[i:(i + seq_length)]
            # 提取序列后面的一个数据点作为目标值
            y = data[i + seq_length]
            # 将输入序列添加到 xs 列表中
            xs.append(x)
            # 将目标值添加到 ys 列表中
            ys.append(y)
        # 将输入序列列表和目标值列表转换为 NumPy 数组，并返回
        return np.array(xs), np.array(ys)

    X, y = create_sequences(data, sequence_length)

    # 加载已经训练好的模型，并确保使用正确的损失函数
    model = load_model(model_path, compile=False)
    # 再编译，使用字符串 'mse' 作为损失函数，并指定一个优化器，例如 'adam'
    model.compile(loss='mse', optimizer='adam') 
    print(f"模型已加载：{model_path}")

    # 模型预测
    y_pred = model.predict(X)

    # 反归一化
    y_test = scaler.inverse_transform(y)
    y_pred = scaler.inverse_transform(y_pred)

    # 计算评估指标
    mse = mean_squared_error(y_test, y_pred)
    rmse = np.sqrt(mse)
    mae = mean_absolute_error(y_test, y_pred)
    print(f"均方误差 (MSE): {mse:.2f}")
    print(f"均方根误差 (RMSE): {rmse:.2f}")
    print(f"平均绝对误差 (MAE): {mae:.2f}")

    # 可视化结果
    plt.figure(figsize=(12, 6))
    plt.plot(df.index[-len(y_test):], y_test, label=f'{region_name} 真实值', color='blue', linewidth=1)  # 使用df的索引
    plt.plot(df.index[-len(y_test):], y_pred, label=f'{region_name} 预测值', color='red', linewidth=1)  # 使用df的索引
    plt.title(f"{region_name} 能源消耗预测 (TCN)")
    plt.xlabel("时间")
    plt.ylabel(target_column)
    plt.legend()
    plt.grid()

    # 创建 runs 目录及其子目录 (如果不存在)
    runs_dir = "runs"
    images_dir = os.path.join(runs_dir, "images_full")
    os.makedirs(images_dir, exist_ok=True)

    # 保存结果图
    result_plot_file = os.path.join(images_dir, f"{region_name}_TCN_prediction_plot.png")
    plt.savefig(result_plot_file)
    # plt.show()
    print(f"预测结果图已保存为：{result_plot_file}")

if __name__ == "__main__":
    csv_file_path = "Data/AEP_hourly.csv"  # 输入数据文件路径
    model_file_path = "runs/models/AEP_hourly_tcn_model.h5"  # 输入已训练的Keras模型路径
    apply_model(csv_file_path, model_file_path)
