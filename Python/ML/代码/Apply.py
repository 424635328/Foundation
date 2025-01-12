import os
import pandas as pd
import xgboost as xgb
import numpy as np
import matplotlib.pyplot as plt
from sklearn.metrics import mean_squared_error, mean_absolute_error
from datetime import datetime

# 设置字体以防止中文乱码
from matplotlib import rcParams
rcParams['font.sans-serif'] = ['SimHei']
rcParams['axes.unicode_minus'] = False

def apply_model(file_path, model_path):
    """
    加载已训练的模型，对整个数据集进行预测，并评估模型。
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

    # 加载已经训练好的模型
    model = xgb.XGBRegressor()
    model.load_model(model_path)
    print(f"模型已加载：{model_path}")

    # 模型预测
    y_pred = model.predict(X)

    # 计算评估指标
    mse = mean_squared_error(y, y_pred)
    rmse = np.sqrt(mse)
    mae = mean_absolute_error(y, y_pred)
    print(f"均方误差 (MSE): {mse:.2f}")
    print(f"均方根误差 (RMSE): {rmse:.2f}")
    print(f"平均绝对误差 (MAE): {mae:.2f}")

    # 可视化结果
    plt.figure(figsize=(12, 6))
    plt.plot(df.index, y, label=f'{region_name} 真实值', color='blue', linewidth=1)
    plt.plot(df.index, y_pred, label=f'{region_name} 预测值', color='red', linewidth=1)
    plt.title(f"{region_name} 能源消耗预测(XGBoost)")
    plt.xlabel("时间")
    plt.ylabel(target_column)  # 使用目标列名称
    plt.legend()
    plt.grid()
    # plt.show()

    # 创建 runs 目录及其子目录 (如果不存在)
    runs_dir = "runs"
    images_dir = os.path.join(runs_dir, "images_full")
    os.makedirs(images_dir, exist_ok=True)


    # 保存结果图
    result_plot_file = os.path.join(images_dir, f"{region_name}_XGBoost_prediction_plot.png")
    plt.savefig(result_plot_file)
    # plt.show()
    print(f"预测结果图已保存为：{result_plot_file}")

if __name__ == "__main__":
    csv_file_path = "Data/AEP_hourly.csv"  # 输入数据文件路径
    model_file_path = "runs/models/AEP_hourly_xgboost_model.model"  # 输入已训练模型路径
    apply_model(csv_file_path, model_file_path)