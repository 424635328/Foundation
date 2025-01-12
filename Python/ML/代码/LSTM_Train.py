import os
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.metrics import mean_squared_error, mean_absolute_error
import numpy as np
import matplotlib.pyplot as plt
from datetime import datetime
from sklearn.preprocessing import MinMaxScaler
import tensorflow as tf
from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import LSTM, Dense
from tensorflow.keras.callbacks import EarlyStopping
import joblib  # 导入joblib库

# 设置字体以防止中文显示乱码
from matplotlib import rcParams
rcParams['font.sans-serif'] = ['SimHei']  # 设置中文字体为SimHei
rcParams['axes.unicode_minus'] = False  # 解决负号显示问题

def create_lstm_model(input_shape):
    model = Sequential()
    model.add(LSTM(50, activation='relu', input_shape=input_shape))
    model.add(Dense(1))
    model.compile(optimizer='adam', loss='mse')
    return model

def create_sequences(data, seq_length, target_column_index):
    xs = []
    ys = []
    for i in range(len(data) - seq_length):
        x = data[i:(i+seq_length)]
        y = data[i + seq_length, target_column_index]  # 目标列的位置
        xs.append(x)
        ys.append(y)
    return np.array(xs), np.array(ys)

def prepare_data(df, target_column):
    """准备数据，包括特征工程、时间特征、滞后特征和归一化。"""
    # 提取时间特征
    df['hour'] = df.index.hour
    df['day'] = df.index.day
    df['month'] = df.index.month
    df['year'] = df.index.year

    # 滞后特征
    for lag in range(1, 25):
        df[f'lag_{lag}'] = df[target_column].shift(lag)

    df.dropna(inplace=True)

    # 缩放所有特征列
    scaler = MinMaxScaler()
    scaled_data = scaler.fit_transform(df)
    return scaled_data, scaler # 返回缩放器

def train_and_evaluate_lstm(file_path):
    """使用LSTM模型进行训练和评估。"""
    base_name = os.path.basename(file_path)
    region_name = os.path.splitext(base_name)[0]

    print(f"加载数据文件：{file_path}")
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

    # 拆分训练集和测试集
    train_df, test_df = train_test_split(df, test_size=0.2, shuffle=False)

    # 准备数据
    scaled_train_data, scaler = prepare_data(train_df, target_column) # 获取缩放器
    scaled_test_data, _ = prepare_data(test_df, target_column) # 测试数据使用训练数据的缩放器

    # 创建 LSTM 数据集 (使用所有特征列)
    seq_length = 24
    X_train_lstm, y_train_lstm = create_sequences(scaled_train_data, seq_length, train_df.columns.get_loc(target_column))
    X_test_lstm, y_test_lstm = create_sequences(scaled_test_data, seq_length, test_df.columns.get_loc(target_column))

    # 创建并训练 LSTM 模型
    input_shape = (X_train_lstm.shape[1], X_train_lstm.shape[2])
    model = create_lstm_model(input_shape)

    # 使用早期停止来避免过拟合
    early_stopping = EarlyStopping(monitor='val_loss', patience=5, restore_best_weights=True)

    # 记录训练开始时间
    start_time = datetime.now()
    print(f"训练开始时间：{start_time}")

    model.fit(X_train_lstm, y_train_lstm, epochs=20, batch_size=32, validation_data=(X_test_lstm, y_test_lstm),
              callbacks=[early_stopping], verbose=1)

    # 记录训练结束时间
    end_time = datetime.now()
    print(f"训练结束时间：{end_time}")

    # 计算训练时长
    training_duration = end_time - start_time
    print(f"训练时长：{training_duration}")

    # 预测
    y_pred_scaled = model.predict(X_test_lstm)

    # 反归一化预测结果 (仅反归一化目标列)
    y_pred_scaled_reshaped = np.repeat(y_pred_scaled, scaled_test_data.shape[1], axis=1) # 将预测结果扩展到与scaled_test_data相同的列数
    y_pred_full = scaler.inverse_transform(y_pred_scaled_reshaped) # 反转所有特征的缩放
    y_pred = y_pred_full[:, train_df.columns.get_loc(target_column)] # 提取目标列

    y_test_lstm_reshaped = np.repeat(y_test_lstm.reshape(-1, 1), scaled_test_data.shape[1], axis=1)
    y_test_full = scaler.inverse_transform(y_test_lstm_reshaped)
    y_test = y_test_full[:, train_df.columns.get_loc(target_column)]

    # 评估模型
    mse = mean_squared_error(y_test, y_pred)
    rmse = np.sqrt(mse)
    mae = mean_absolute_error(y_test, y_pred)
    print(f"均方误差 (MSE): {mse:.2f}")
    print(f"均方根误差 (RMSE): {rmse:.2f}")
    print(f"平均绝对误差 (MAE): {mae:.2f}")

    # 可视化预测结果
    plt.figure(figsize=(12, 6))
    plt.plot(test_df.index[seq_length:], test_df[target_column][seq_length:], label=f'{region_name} 真实值', color='blue', linewidth=1)
    plt.plot(test_df.index[seq_length:], y_pred, label=f'{region_name} 预测值', color='red', linewidth=1)
    plt.title(f"{region_name} 能源消耗预测")
    plt.xlabel("时间")
    plt.ylabel(target_column)
    plt.legend()
    plt.grid()

    # 创建 runs 目录及其子目录，用于保存模型和结果图
    runs_dir = "runs"
    models_dir = os.path.join(runs_dir, "models")
    images_dir = os.path.join(runs_dir, "images")

    os.makedirs(runs_dir, exist_ok=True)
    os.makedirs(models_dir, exist_ok=True)
    os.makedirs(images_dir, exist_ok=True)

    # 保存预测结果图
    result_plot_file = os.path.join(images_dir, f"{region_name}_lstm_prediction_plot.png")
    plt.savefig(result_plot_file)
    plt.show()
    print(f"预测结果图已保存为：{result_plot_file}")

    # 保存LSTM模型和缩放器
    model_file = os.path.join(models_dir, f"{region_name}_lstm_model.h5")
    model.save(model_file)

    scaler_file = os.path.join(models_dir, f"{region_name}_scaler.pkl")
    joblib.dump(scaler, scaler_file)

    print(f"模型已保存为：{model_file}")
    print(f"缩放器已保存为：{scaler_file}")

# 主函数入口
if __name__ == "__main__":
    csv_file_path = "Data/COMED_hourly.csv"  # 数据文件路径
    train_and_evaluate_lstm(csv_file_path)  # 调用训练和评估函数
