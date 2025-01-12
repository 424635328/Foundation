import numpy as np
import pandas as pd
from collections import Counter
import matplotlib.pyplot as plt
import graphviz
from sklearn.datasets import load_iris
import os
from tqdm import tqdm

# 设置matplotlib支持中文显示
plt.rcParams['font.sans-serif'] = ['SimHei']  # 用来正常显示中文标签
plt.rcParams['axes.unicode_minus'] = False  # 用来正常显示负号

class ID3:
    def __init__(self, max_depth=None, min_samples=1, max_recursion=1000, purity_threshold=1.0):
        """
        初始化ID3决策树
        """
        self.max_depth = max_depth
        self.min_samples = min_samples
        self.max_recursion = max_recursion
        self.purity_threshold = purity_threshold
        self.tree = None
        self.feature_names = None
        self.class_names = None
        self.total_nodes = 0  # 用于跟踪节点总数

    def calculate_entropy(self, y):
        """计算熵"""
        counter = Counter(y)
        entropy = 0
        for count in counter.values():
            p = count / len(y)
            entropy -= p * np.log2(p)
        return entropy

    def calculate_information_gain(self, X, y, feature_idx):
        """计算信息增益"""
        parent_entropy = self.calculate_entropy(y)
        unique_values = set(X[:, feature_idx])
        
        weighted_entropy = 0
        for value in unique_values:
            mask = X[:, feature_idx] == value
            child_y = y[mask]
            weight = len(child_y) / len(y)
            weighted_entropy += weight * self.calculate_entropy(child_y)
            
        return parent_entropy - weighted_entropy

    def _should_stop(self, X, y, depth, recursion_count):
        """检查是否满足终止条件并可视化"""
        stop_reason = None
        
        if len(set(y)) == 1:
            stop_reason = "所有样本属于同一类别"
        elif X.shape[1] == 0:
            stop_reason = "没有更多特征可用"
        elif self.max_depth and depth >= self.max_depth:
            stop_reason = f"达到最大深度 {self.max_depth}"
        elif len(y) <= self.min_samples:
            stop_reason = f"样本数 {len(y)} 小于最小阈值 {self.min_samples}"
        elif Counter(y).most_common(1)[0][1] / len(y) >= self.purity_threshold:
            stop_reason = "达到数据纯度阈值"
        elif recursion_count >= self.max_recursion:
            stop_reason = "超过最大递归次数"
            
        if stop_reason:
            self._visualize_stop_condition(X, y, depth, stop_reason)
            return True
        return False

    def _build_tree(self, X, y, available_features, depth=0, recursion_count=0, pbar=None):
        """递归构建决策树"""
        self.total_nodes += 1
        if pbar:
            pbar.update(1)
            pbar.set_description(f'构建节点 {self.total_nodes}')
            
        if self._should_stop(X, y, depth, recursion_count):
            return Counter(y).most_common(1)[0][0]

        # 计算每个特征的信息增益
        information_gains = [
            (i, self.calculate_information_gain(X, y, i))
            for i in available_features
        ]
        
        best_feature_idx, max_gain = max(information_gains, key=lambda x: x[1])
        
        tree = {
            'feature_idx': best_feature_idx,
            'children': {}
        }
        
        for value in set(X[:, best_feature_idx]):
            mask = X[:, best_feature_idx] == value
            if sum(mask) > 0:
                new_available_features = available_features - {best_feature_idx}
                subtree = self._build_tree(
                    X[mask], 
                    y[mask],
                    new_available_features,
                    depth + 1,
                    recursion_count + 1,
                    pbar
                )
                tree['children'][value] = subtree
                
        return tree

    def fit(self, X, y):
        """训练决策树"""
        self.total_nodes = 0
        # 估计最大可能的节点数（用于进度条）
        max_possible_nodes = min(2 ** (self.max_depth if self.max_depth else 10), len(X))
        
        with tqdm(total=max_possible_nodes, desc="构建决策树") as pbar:
            self.tree = self._build_tree(
                X, 
                y,
                available_features=set(range(X.shape[1])),
                pbar=pbar
            )
            pbar.update(max_possible_nodes - self.total_nodes)  # 确保进度条完成
            
        return self

    def predict_one(self, x, tree=None):
        """预测单个样本"""
        if tree is None:
            tree = self.tree
            
        # 如果树是叶子节点（即类别标签）
        if not isinstance(tree, dict):
            return tree
            
        feature_idx = tree['feature_idx']
        value = x[feature_idx]
        
        # 如果测试样本的特征值在训练时没有见过，返回最常见的类别
        if value not in tree['children']:
            return max(
                (self.predict_one(x, subtree) for subtree in tree['children'].values()),
                key=lambda x: Counter(str(x)).most_common(1)[0][1]
            )
            
        return self.predict_one(x, tree['children'][value])

    def predict(self, X):
        """预测多个样本"""
        predictions = []
        for x in tqdm(X, desc="预测样本"):
            predictions.append(self.predict_one(x))
        return np.array(predictions)

    def _visualize_stop_condition(self, X, y, depth, reason):
        """可视化终止条件"""
        plt.figure(figsize=(10, 6))
        
        # 如果数据是二维的，绘制散点图
        if X.shape[1] >= 2:
            unique_labels = np.unique(y)
            colors = plt.cm.rainbow(np.linspace(0, 1, len(unique_labels)))
            
            for label, color in zip(unique_labels, colors):
                mask = (y == label)
                plt.scatter(X[mask, 0], X[mask, 1], 
                          color=color,
                          label=f'类别 {self.class_names[label] if self.class_names is not None else label}')
        
        # 如果是一维数据，绘制直方图
        elif X.shape[1] == 1:
            unique_labels = np.unique(y)
            colors = plt.cm.rainbow(np.linspace(0, 1, len(unique_labels)))
            
            for label, color in zip(unique_labels, colors):
                mask = (y == label)
                plt.hist(X[mask, 0], alpha=0.5, 
                        color=color,
                        label=f'类别 {self.class_names[label] if self.class_names is not None else label}')
        
        plt.title(f'深度 {depth}: {reason}\n样本数: {len(y)}')
        plt.legend()
        
        # 创建输出目录
        os.makedirs('visualization', exist_ok=True)
        plt.savefig(f'visualization/stop_condition_depth_{depth}.png')
        plt.close()

    def visualize_tree(self, output_file='tree'):
        """使用graphviz可视化决策树"""
        try:
            dot = graphviz.Digraph(comment='ID3决策树')
            
            def add_nodes(tree, parent_id='0'):
                if not isinstance(tree, dict):
                    label = self.class_names[int(tree)] if self.class_names is not None else str(tree)
                    dot.node(parent_id, f'类别: {label}', shape='box')
                    return

                feature_name = (self.feature_names[tree['feature_idx']] 
                              if self.feature_names is not None
                              else f'特征 {tree["feature_idx"]}')
                dot.node(parent_id, feature_name)

                for value, subtree in tree['children'].items():
                    child_id = f'{parent_id}_{value}'
                    add_nodes(subtree, child_id)
                    dot.edge(parent_id, child_id, f'{value:.2f}')

            add_nodes(self.tree)
            dot.attr(fontname='SimHei')
            
            # 创建输出目录
            os.makedirs('visualization', exist_ok=True)
            
            try:
                dot.render(output_file, directory='visualization', view=False)
                print("决策树可视化文件已保存。")
            except graphviz.backend.execute.ExecutableNotFound:
                print("警告：未找到Graphviz执行文件。请确保已安装Graphviz并将其添加到系统PATH中。")
                print("您可以从这里下载Graphviz：https://graphviz.org/download/")
                # 保存原始的DOT文件作为备选
                dot_file = os.path.join('visualization', f'{output_file}.dot')
                with open(dot_file, 'w', encoding='utf-8') as f:
                    f.write(dot.source)
                print(f"已将决策树结构保存为DOT文件：{dot_file}")
        except Exception as e:
            print(f"生成决策树可视化时发生错误：{str(e)}")

def main():
    # 加载iris数据集
    print("加载数据集...")
    iris = load_iris()
    X, y = iris.data, iris.target
    
    # 创建ID3分类器
    print("\n初始化ID3分类器...")
    clf = ID3(
        max_depth=3,
        min_samples=5,
        max_recursion=100,
        purity_threshold=0.95
    )
    
    # 设置特征名和类别名
    clf.feature_names = iris.feature_names
    clf.class_names = iris.target_names
    
    # 训练模型
    print("\n开始训练模型...")
    clf.fit(X, y)
    
    # 可视化决策树
    print("\n生成决策树可视化...")
    clf.visualize_tree()
    
    # 进行预测
    print("\n对训练数据进行预测...")
    predictions = clf.predict(X)
    
    # 计算准确率
    accuracy = np.mean(predictions == y)
    print(f"\n训练集准确率: {accuracy:.2%}")
    print("\n决策树训练完成！可视化结果已保存在 visualization 目录下。")

if __name__ == "__main__":
    main()
