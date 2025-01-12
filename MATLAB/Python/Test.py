import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from sklearn.impute import SimpleImputer

# 导入数据集
train_data = pd.read_csv('train.csv')
test_data = pd.read_csv('test.csv')
sample_submission_data = pd.read_csv('sample_submission.csv')

# 删除 ID 列
train_data = train_data.drop('Id', axis=1)
test_data = test_data.drop('Id', axis=1)

# 查看前5个训练集数据
print('前5个训练集数据：')
print(train_data.head())

# 查看前5个测试集数据
print('前5个测试集数据：')
print(test_data.head())

# 假设你有一个房价数据集，其中包含'LotArea'和'SalePrice'两列
# 加载数据集
# 读取包含训练数据的表格
train_data = pd.read_csv('train.csv')

# 获取ID列的数据
IdColumn = train_data['Id']

# 读取包含训练数据的表格
#trainData = readtable('train.csv');

#MSZoningColumn = trainData.MSZoning;
train_data['Id'] = train_data['Id'].astype(str)
train_data['MSZoning'] = train_data['MSZoning'].astype(str)

# 合并训练集和测试集
all_data = pd.concat([train_data, test_data], axis=0)

# 计算每列的缺失率
missing_rates = all_data.isnull().sum() / len(all_data) * 100

# 绘制缺失率柱状图
plt.figure()
plt.bar(missing_rates.index, missing_rates.values)
plt.xlabel('Features')
plt.ylabel('Missing Rate (%)')
plt.xticks(rotation=45)
plt.title('Missing Values Rates')
plt.show()

# 填补缺失值，这里使用均值填充
imputer = SimpleImputer(strategy='mean')
all_data = pd.DataFrame(imputer.fit_transform(all_data), columns=all_data.columns)

# 分离特征和目标变量
X = all_data.iloc[:, :-1]
y = all_data.iloc[:, -1]

# 计算特征之间的相关性矩阵
correlation_matrix = X.corr()

# 创建热图
plt.figure()
plt.imshow(correlation_matrix, cmap='jet')
plt.colorbar()
plt.xticks(np.arange(len(correlation_matrix.columns)), correlation_matrix.columns, rotation=45)
plt.yticks(np.arange(len(correlation_matrix.columns)), correlation_matrix.columns)
plt.title('特征相关性热图')
plt.show()