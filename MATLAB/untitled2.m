import matlab.stats.*
% 导入 Curve Fitting Toolbox
import matlab.curvefit.*
% 导入 Neural Network Toolbox
import matlab.nnet.*
% 导入 Optimization Toolbox
import matlab.optim.*
% 导入 Parallel Computing Toolbox
import matlab.parallel.*
%导入数据集
opts = detectImportOptions('train.csv'); % 检测导入选项
opts.VariableNamingRule = 'preserve'; % 设置变量命名规则为 'preserve'
train_data = readtable('train.csv', opts); % 使用设置好的选项读取数据
% 检测导入选项并设置 VariableNamingRule 为 'preserve'
opts_train_data = detectImportOptions('train.csv');
opts_train_data.VariableNamingRule = 'preserve';
% 读取 train 数据集
train_data = readtable('train.csv', opts_train_data);
% 删除 train 数据集中的 ID 列
train_data = removevars(train_data, 'Id');
% 检测导入选项并设置 VariableNamingRule 为 'preserve'
opts_test = detectImportOptions('test.csv');
opts_test.VariableNamingRule = 'preserve';
% 读取 test 数据集
test_data = readtable('test.csv', opts_test);
% 删除 test 数据集中的 ID 列
test_data = removevars(test_data, 'Id');
% 查看前5个训练集数据
fprintf('前5个训练集数据：');
disp(train_data(1:5, :));
% 查看前5个测试集数据
fprintf('前5个测试集数据：');
disp(test_data(1:5, :));
% 假设你有一个房价数据集，其中包含'LotArea'和'SalePrice'两列
% 加载数据集
% 读取 train 数据集
train_data = readtable('train.csv', opts);
% 检测导入选项并设置 VariableNamingRule 为 'preserve'
opts = detectImportOptions('test.csv');
opts.VariableNames = 'preserve';
% 读取 test 数据集
test_data = readtable('test.csv', opts);
sample_submission_data=readtable('sample_submission.csv',opts);
% 提取'LotArea'列
LotArea = train_data.LotArea;
SalePrice=train_data.SalePrice;
% 计算'LotArea'的均值
mean_LotArea = mean(LotArea);
disp(['LotArea的均值为：', num2str(mean_LotArea)]);
% 计算均值和标准差
mean_LotArea = mean(LotArea);
std_LotArea = std(LotArea);
mean_SalePrice=mean(SalePrice);
mean_SalePrice= mean(SalePrice);
std_SalePrice = std(SalePrice);
% 定义阈值（例如，3倍标准差）
threshold = 3;
% 计算上下界
upper_bound_LotArea = mean_LotArea + threshold * std_LotArea;
lower_bound_LotArea = mean_LotArea - threshold * std_LotArea;
upper_bound_SalePrice = mean_SalePrice + threshold * std_SalePrice;
lower_bound_SalePrice = mean_SalePrice - threshold * std_SalePrice;
% 找出离群值的索引
   scatter(train_data.LotArea, train_data.SalePrice, 'b', 'filled'); % 假设'LotArea'和'Price'是数据集中的变量名
   outliers_LotArea = LotArea > upper_bound_LotArea | LotArea< lower_bound_LotArea;
   outliers_SalePrice = SalePrice > upper_bound_SalePrice |SalePrice< lower_bound_SalePrice;
% 加载数据
% 读取包含训练数据的表格
trainData = readtable('train.csv');

% 获取ID列的数据
IdColumn = trainData.Id;
% 读取包含训练数据的表格
%trainData = readtable('train.csv');


%MSZoningColumn = trainData.MSZoning;
train_data.Id = num2str(train_data.Id);
train_data.MSZoning = cell2mat(train_data.MSZoning);
% 合并训练集和测试集

  % IdCell = num2cell(trainData.Id);
     % MSZoningDouble = str2double(trainData.MSZoning);
        % result = string(train_data.Id) + string(train_data.MSZoning);
            result = strjoin({train_data.Id, train_data.MSZoning}, ' ');
% 现在 'Id' 和 'MSZoning' 都是 cell 类型，可以进行串联
result = strcat(train_data.Id, train_data.MSZoning);
all_data = [train_data.Variables; test_data.Variables];
all_data = array2table(all_data, 'VariableNames',sample_submission.Properties.VariableNames);

% 计算每列的缺失率
missing_rates = sum(ismissing(all_data)) / height(all_data) * 100;

% 绘制缺失率柱状图
figure;
bar(missing_rates);
xlabel('Features');
ylabel('Missing Rate (%)');
xticklabels(all_data.Properties.VariableNames);
xtickangle(45);
title('Missing Values Rates');

% 填补缺失值，这里使用均值填充
all_data = fillmissing(all_data, 'constant', 'DataVariables', 1:end-1, 'Value', 'mean');

% 分离特征和目标变量
X = all_data{:, 1:end-1};
y = all_data{:, end};

% 在这里添加任何其他特征工程或模型训练的步骤

% 创建热图
figure;
heatmap(correlation_matrix, 'Colormap', 'jet', 'ColorbarVisible', 'on', 'XLabel', '特征', 'YLabel', '特征', 'Title', '特征相关性热图');