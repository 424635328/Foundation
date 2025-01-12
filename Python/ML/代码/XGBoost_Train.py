import os
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.metrics import mean_squared_error, mean_absolute_error
import xgboost as xgb
import numpy as np
import matplotlib.pyplot as plt
from datetime import datetime

# 设置字体以防止中文显示乱码
from matplotlib import rcParams
rcParams['font.sans-serif'] = ['SimHei']  # 设置中文字体为SimHei
rcParams['axes.unicode_minus'] = False  # 解决负号显示问题

def train_and_evaluate_model(file_path):
    """
    训练和评估XGBoost回归模型。
    该函数负责从给定的CSV文件路径加载数据，进行特征工程，训练XGBoost回归模型，
    然后评估并保存预测结果。
    """

    # 从文件路径中提取地区名称，用于模型保存文件的命名
    base_name = os.path.basename(file_path)
    region_name = os.path.splitext(base_name)[0]  # 提取文件名作为地区名称

    # 加载数据集
    print(f"加载数据文件：{file_path}")
    df = pd.read_csv(file_path)

    # 检查数据集的列名，确保包含必要的列
    print(f"数据集列名：{df.columns}")

    # 确保数据集包含 'Datetime' 列并将其转化为日期时间格式
    if 'Datetime' not in df.columns:
        raise ValueError("'Datetime' 列在数据中不存在，请检查数据格式。")
    df['Datetime'] = pd.to_datetime(df['Datetime'])  # 转换为日期时间格式
    df.set_index('Datetime', inplace=True)  # 将'Datetime'列设置为索引

    # 确认目标列名，即能源消耗列
    target_column = None
    for col in df.columns:
        if 'MW' in col:  # 假设目标列名称中包含 'MW'
            target_column = col
            break
    if target_column is None:
        raise ValueError("未找到合适的目标列，请检查数据中的能源消耗列。")
    print(f"目标列：{target_column}")

    # 划分训练集和测试集，保持时间序列顺序（不打乱）
    train_df, test_df = train_test_split(df, test_size=0.2, shuffle=False)

    # 特征工程：提取时间特征
    for df_part in [train_df, test_df]:
        df_part['hour'] = df_part.index.hour  # 小时
        df_part['day'] = df_part.index.day  # 日期
        df_part['month'] = df_part.index.month  # 月份
        df_part['year'] = df_part.index.year  # 年份

    # 添加滞后特征：根据目标列的前24小时数据生成滞后特征
    for lag in range(1, 25):
        train_df[f'lag_{lag}'] = train_df[target_column].shift(lag)  # 为训练集添加滞后特征
        test_df[f'lag_{lag}'] = test_df[target_column].shift(lag)  # 为测试集添加滞后特征

    # 删除包含NaN的行，确保数据整洁
    train_df.dropna(inplace=True)
    test_df.dropna(inplace=True)

    # 特征矩阵与目标变量
    X_train = train_df.drop(columns=[target_column])  # 训练特征
    y_train = train_df[target_column]  # 训练目标变量
    X_test = test_df.drop(columns=[target_column])  # 测试特征
    y_test = test_df[target_column]  # 测试目标变量

    # 记录训练开始时间
    start_time = datetime.now()
    print(f"训练开始时间：{start_time}")

    # 创建并训练XGBoost回归模型
    model = xgb.XGBRegressor(
        n_estimators=1000,  # 树的个数
        learning_rate=0.1,  # 学习率
        max_depth=5,  # 树的最大深度
        subsample=0.8,  # 随机采样比例
        colsample_bytree=0.8,  # 树的特征采样比例
        random_state=42  # 随机种子，确保结果可复现
    )
    model.fit(X_train, y_train)  # 训练模型

    # 记录训练结束时间
    end_time = datetime.now()
    print(f"训练结束时间：{end_time}")

    # 计算训练时长
    training_duration = end_time - start_time
    print(f"训练时长：{training_duration}")

    # 创建 runs 目录及其子目录，用于保存模型和结果图
    runs_dir = "runs"
    models_dir = os.path.join(runs_dir, "models")
    images_dir = os.path.join(runs_dir, "images")

    os.makedirs(runs_dir, exist_ok=True)  # 创建runs目录
    os.makedirs(models_dir, exist_ok=True)  # 创建models目录
    os.makedirs(images_dir, exist_ok=True)  # 创建images目录

    # 保存训练好的模型
    model_file = os.path.join(models_dir, f"{region_name}_xgboost_model.model")
    model.save_model(model_file)  # 使用XGBoost的save_model方法保存模型
    print(f"模型已保存为：{model_file}")

    # 预测并评估模型
    y_pred = model.predict(X_test)  # 在测试集上进行预测
    mse = mean_squared_error(y_test, y_pred)  # 计算均方误差
    rmse = np.sqrt(mse)  # 计算均方根误差
    mae = mean_absolute_error(y_test, y_pred)  # 计算平均绝对误差
    print(f"均方误差 (MSE): {mse:.2f}")
    print(f"均方根误差 (RMSE): {rmse:.2f}")
    print(f"平均绝对误差 (MAE): {mae:.2f}")

    # 可视化预测结果
    plt.figure(figsize=(12, 6))  # 设置图表大小
    plt.plot(test_df.index, y_test, label=f'{region_name} 真实值', color='blue', linewidth=1)
    plt.plot(test_df.index, y_pred, label=f'{region_name} 预测值', color='red', linewidth=1)
    plt.title(f"{region_name} 能源消耗预测")
    plt.xlabel("时间")
    plt.ylabel(target_column)
    plt.legend()
    plt.grid()

    # 保存预测结果图
    result_plot_file = os.path.join(images_dir, f"{region_name}_XGBoost_prediction_plot.png")
    plt.savefig(result_plot_file)  # 保存图像
    plt.show()  # 显示图像
    print(f"预测结果图已保存为：{result_plot_file}")

# 主函数入口
if __name__ == "__main__":
    csv_file_path = "Data/AEP_hourly.csv"  # 数据文件路径
    train_and_evaluate_model(csv_file_path)  # 调用训练和评估函数
