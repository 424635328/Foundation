import os
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.metrics import mean_squared_error, mean_absolute_error
from tensorflow.keras.models import load_model
from datetime import datetime
from sklearn.preprocessing import MinMaxScaler
import joblib # 导入joblib

# 设置字体以防止中文乱码
from matplotlib import rcParams
rcParams['font.sans-serif'] = ['SimHei']
rcParams['axes.unicode_minus'] = False

def prepare_data(df, target_column):  # 与训练代码中完全相同的函数
    """准备数据，包括特征工程、时间特征、滞后特征。"""
    # 提取时间特征
    df['hour'] = df.index.hour
    df['day'] = df.index.day
    df['month'] = df.index.month
    df['year'] = df.index.year

    # 滞后特征
    for lag in range(1, 25):
        df[f'lag_{lag}'] = df[target_column].shift(lag)

    df.dropna(inplace=True)
    return df

def apply_lstm_model(file_path, model_path,scaler_path):
    """
    加载已训练的LSTM模型，对整个数据集进行预测，并评估模型。
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

    # 特征工程：提取时间特征
    df['hour'] = df.index.hour
    df['day'] = df.index.day
    df['month'] = df.index.month
    df['year'] = df.index.year

    # 滞后特征
    for lag in range(1, 25):  # 滞后 1 到 24 小时
        df[f'lag_{lag}'] = df[target_column].shift(lag)

    # 删除包含 NaN 的行
    df.dropna(inplace=True)

    # 准备特征和标签
    X = df.drop(columns=[target_column])
    y = df[target_column]

    # 归一化特征
    scaler = MinMaxScaler()
    X_scaled = scaler.fit_transform(X)

    # 加载已经训练好的LSTM模型
    model = load_model(model_path, compile=False)
    # 再编译，使用字符串 'mse' 作为损失函数，并指定一个优化器，例如 'adam'
    model.compile(loss='mse', optimizer='adam') 

    # 加载缩放器
    scaler = joblib.load(scaler_path)

    #  准备数据 (使用与训练数据相同的特征工程)
    df = prepare_data(df, target_column)

    # 使用加载的缩放器缩放数据
    scaled_data = scaler.transform(df)


    # 创建 LSTM 输入数据
    seq_length = 24
    X_lstm = np.array([scaled_data[i-seq_length:i, :] for i in range(seq_length, len(scaled_data))])
    y_lstm = df[target_column].values[seq_length:]

    # 模型预测
    y_pred_scaled = model.predict(X_lstm)

    # 反归一化预测结果 (使用加载的缩放器)
    y_pred = scaler.inverse_transform(np.concatenate((scaled_data[seq_length:, :-1], y_pred_scaled), axis=1))[:, -1]

    # 计算评估指标
    mse = mean_squared_error(y_lstm, y_pred)
    rmse = np.sqrt(mse)
    mae = mean_absolute_error(y_lstm, y_pred)
    print(f"均方误差 (MSE): {mse:.2f}")
    print(f"均方根误差 (RMSE): {rmse:.2f}")
    print(f"平均绝对误差 (MAE): {mae:.2f}")

    # 可视化结果
    plt.figure(figsize=(12, 6))
    plt.plot(df.index[seq_length:], y_lstm, label=f'{region_name} 真实值', color='blue', linewidth=1)
    plt.plot(df.index[seq_length:], y_pred, label=f'{region_name} 预测值', color='red', linewidth=1)
    plt.title(f"{region_name} 能源消耗预测(LSTM)")
    plt.xlabel("时间")
    plt.ylabel(target_column)  # 使用目标列名称
    plt.legend()
    plt.grid()

    # 创建 runs 目录及其子目录 (如果不存在)
    runs_dir = "runs"
    images_dir = os.path.join(runs_dir, "images_full")
    os.makedirs(images_dir, exist_ok=True)

    # 保存结果图
    result_plot_file = os.path.join(images_dir, f"{region_name}_LSTM_prediction_plot.png")
    plt.savefig(result_plot_file)
    # plt.show()
    print(f"预测结果图已保存为：{result_plot_file}")

if __name__ == "__main__":
    csv_file_path = "Data/COMED_hourly.csv"
    model_file_path = "runs/models/COMED_hourly_lstm_model.h5"
    scaler_file_path = "runs/models/COMED_hourly_scaler.pkl" # 缩放器文件路径
    apply_lstm_model(csv_file_path, model_file_path, scaler_file_path)
