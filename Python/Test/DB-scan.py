import numpy as np
import matplotlib.pyplot as plt
from sklearn.datasets import make_moons
import os
from tqdm import tqdm
import matplotlib.animation as animation
from sklearn.metrics import pairwise_distances, silhouette_score, calinski_harabasz_score
import time
import logging
from typing import Tuple, Dict, List, Optional, Union
import warnings

# 配置matplotlib支持中文显示
plt.rcParams['font.sans-serif'] = ['SimHei', 'Microsoft YaHei', 'KaiTi', 'SimSun', 'NSimSun']  # 按优先级尝试加载中文字体
plt.rcParams['axes.unicode_minus'] = False  # 用来正常显示负号
plt.rcParams['font.family'] = 'sans-serif'  # 设置字体族

# 配置日志
logging.basicConfig(
    level=logging.INFO,
    format='%(asctime)s - %(levelname)s - %(message)s',
    handlers=[
        logging.FileHandler('dbscan.log', encoding='utf-8'),
        logging.StreamHandler()
    ]
)

class DataGenerator:
    """数据生成器：用于生成不同类型的测试数据集"""
    
    @staticmethod
    def generate_complex_dataset(
        n_circle: int = 150,
        n_gaussian: int = 150,
        n_crescent: int = 150,
        n_noise: int = 50,
        noise_range: Tuple[float, float] = (-6, 6),
        random_state: Optional[int] = None
    ) -> np.ndarray:
        """
        生成复杂的测试数据集
        
        参数:
            n_circle: 每个圆形的点数
            n_gaussian: 高斯分布簇点数
            n_crescent: 新月形状的点数
            n_noise: 噪声点数量
            noise_range: 噪声点的范围
            random_state: 随机种子
            
        返回:
            np.ndarray: 生成的数据集
        """
        if random_state is not None:
            np.random.seed(random_state)
            
        try:
            # 生成同心圆
            t = np.linspace(0, 2*np.pi, n_circle)
            inner_circle = np.c_[np.cos(t), np.sin(t)] * 2
            outer_circle = np.c_[np.cos(t), np.sin(t)] * 4
            
            # 生成高斯分布簇
            gaussian_cluster = np.random.normal(
                loc=[-4, -4], 
                scale=0.3, 
                size=(n_gaussian, 2)
            )
            
            # 生成新月形状
            t = np.linspace(0, np.pi, n_crescent)
            crescent = np.c_[np.cos(t), np.sin(t)] * 3
            crescent = crescent + np.array([6, 0])
            
            # 生成随机噪声点
            noise = np.random.uniform(
                low=noise_range[0], 
                high=noise_range[1], 
                size=(n_noise, 2)
            )
            
            # 合并所有数据
            X = np.vstack([
                inner_circle,
                outer_circle,
                gaussian_cluster,
                crescent,
                noise
            ])
            
            # 添加小的随机扰动
            X += np.random.normal(0, 0.1, X.shape)
            
            return X
            
        except Exception as e:
            logging.error(f"数据生成失败: {str(e)}")
            raise

class DBSCAN:
    """DBSCAN聚类算法实现"""
    
    def __init__(
        self, 
        eps: float = 0.5, 
        min_samples: int = 5,
        metric: str = 'euclidean'
    ):
        """
        初始化DBSCAN聚类��
        
        参数:
            eps: 邻域半径
            min_samples: 核心点的最小邻域样本数
            metric: 距离度量方式
        """
        self._validate_parameters(eps, min_samples)
        self.eps = eps
        self.min_samples = min_samples
        self.metric = metric
        self.labels = None
        self.history = []
        self.execution_time = None
        
    @staticmethod
    def _validate_parameters(eps: float, min_samples: int) -> None:
        """验证参数有效性"""
        if eps <= 0:
            raise ValueError("eps必须大于0")
        if min_samples < 1:
            raise ValueError("min_samples必须大于等于1")
            
    def _find_neighbors(self, X: np.ndarray, point_idx: int) -> np.ndarray:
        """查找邻域点"""
        distances = pairwise_distances(
            X[point_idx].reshape(1, -1),
            X,
            metric=self.metric
        ).ravel()
        return np.where(distances <= self.eps)[0]
        
    def fit(self, X: np.ndarray) -> 'DBSCAN':
        """
        训练DBSCAN模型
        
        参数:
            X: 输入数据矩阵
            
        返回:
            self: 训练好的模型
        """
        start_time = time.time()
        
        try:
            n_samples = X.shape[0]
            self.labels = np.full(n_samples, -1)
            
            # 记录初始状态
            self.history = [{
                'labels': self.labels.copy(),
                'current_point': None,
                'neighbors': None,
                'title': "初始状态"
            }]
            
            cluster_label = 0
            
            with tqdm(total=n_samples, desc="DBSCAN聚类") as pbar:
                for point_idx in range(n_samples):
                    pbar.update(1)
                    
                    if self.labels[point_idx] != -1:
                        continue
                        
                    neighbors = self._find_neighbors(X, point_idx)
                    
                    self.history.append({
                        'labels': self.labels.copy(),
                        'current_point': point_idx,
                        'neighbors': neighbors,
                        'title': f"检查点 {point_idx} 的邻域"
                    })
                    
                    if len(neighbors) < self.min_samples:
                        continue
                        
                    self.labels[point_idx] = cluster_label
                    
                    self.history.append({
                        'labels': self.labels.copy(),
                        'current_point': point_idx,
                        'neighbors': neighbors,
                        'title': f"发现新簇 {cluster_label}"
                    })
                    
                    self._expand_cluster(X, point_idx, neighbors, cluster_label)
                    cluster_label += 1
                    
            self.execution_time = time.time() - start_time
            return self
            
        except Exception as e:
            logging.error(f"聚类过程发生错误: {str(e)}")
            raise
            
    def _expand_cluster(
        self, 
        X: np.ndarray, 
        point_idx: int, 
        neighbors: np.ndarray, 
        cluster_label: int
    ) -> None:
        """扩展簇"""
        seed_points = list(neighbors)
        for seed_idx in seed_points:
            if self.labels[seed_idx] == -1:
                self.labels[seed_idx] = cluster_label
                
                seed_neighbors = self._find_neighbors(X, seed_idx)
                
                self.history.append({
                    'labels': self.labels.copy(),
                    'current_point': seed_idx,
                    'neighbors': seed_neighbors,
                    'title': f"扩展簇 {cluster_label}"
                })
                
                if len(seed_neighbors) >= self.min_samples:
                    seed_points.extend(n for n in seed_neighbors 
                                    if n not in seed_points)
                    
    def get_params(self) -> Dict:
        """获取模型参数"""
        return {
            'eps': self.eps,
            'min_samples': self.min_samples,
            'metric': self.metric
        }
        
    def get_performance_stats(self) -> Dict:
        """获取性能统计信息"""
        if self.labels is None:
            return {}
            
        return {
            'n_clusters': len(np.unique(self.labels[self.labels != -1])),
            'n_noise': np.sum(self.labels == -1),
            'execution_time': self.execution_time
        }

class ClusterEvaluator:
    """
    聚类评估器：用于评估聚类结果的质量
    
    评估指标：
    1. 轮廓系数 (Silhouette Coefficient)
    2. Calinski-Harabasz指数
    3. 簇内平均距离
    4. 簇间平均距离
    5. Davies-Bouldin指数
    """
    
    def __init__(self, X, labels):
        """
        初始化评估器
        
        参数:
            X: 数据矩阵
            labels: 聚类标签
        """
        self.X = X
        self.labels = labels
        self.n_samples = X.shape[0]
        self.unique_labels = np.unique(labels[labels != -1])  # 排除噪声点
        self.distance_matrix = pairwise_distances(X)
        
    def calculate_silhouette(self):
        """
        计算轮廓系数
        
        返回:
            overall_score: 整体轮廓系数
            cluster_scores: 每个簇的轮廓系数
        """
        try:
            overall_score = silhouette_score(self.X, self.labels)
            cluster_scores = {}
            
            for label in self.unique_labels:
                mask = (self.labels == label)
                if np.sum(mask) > 1:  # 至少需要2个样本
                    cluster_scores[label] = silhouette_score(
                        self.X[self.labels != -1],
                        self.labels[self.labels != -1]
                    )
            
            return overall_score, cluster_scores
        except Exception as e:
            return None, {}
            
    def calculate_ch_score(self):
        """计算Calinski-Harabasz指数"""
        try:
            return calinski_harabasz_score(self.X, self.labels)
        except:
            return None
            
    def calculate_intra_cluster_distances(self):
        """计算簇内平均距离"""
        intra_distances = {}
        
        for label in self.unique_labels:
            mask = (self.labels == label)
            cluster_points = self.X[mask]
            
            if len(cluster_points) > 1:
                distances = pairwise_distances(cluster_points)
                intra_distances[label] = np.mean(distances)
            
        return intra_distances
        
    def calculate_inter_cluster_distances(self):
        """计算簇间平均距离"""
        inter_distances = {}
        
        for label1 in self.unique_labels:
            inter_distances[label1] = {}
            mask1 = (self.labels == label1)
            
            for label2 in self.unique_labels:
                if label1 != label2:
                    mask2 = (self.labels == label2)
                    dist = np.mean(pairwise_distances(
                        self.X[mask1],
                        self.X[mask2]
                    ))
                    inter_distances[label1][label2] = dist
                    
        return inter_distances
        
    def calculate_davies_bouldin(self):
        """计算Davies-Bouldin指数"""
        if len(self.unique_labels) < 2:
            return None
            
        intra_dists = self.calculate_intra_cluster_distances()
        inter_dists = self.calculate_inter_cluster_distances()
        
        db_scores = []
        for label1 in self.unique_labels:
            if label1 not in intra_dists:
                continue
                
            max_ratio = 0
            for label2 in self.unique_labels:
                if label1 != label2 and label2 in intra_dists:
                    ratio = (intra_dists[label1] + intra_dists[label2]) / \
                            inter_dists[label1][label2]
                    max_ratio = max(max_ratio, ratio)
                    
            db_scores.append(max_ratio)
            
        return np.mean(db_scores) if db_scores else None
        
    def evaluate(self):
        """执行完整的评估"""
        results = {
            'sample_count': self.n_samples,
            'cluster_count': len(self.unique_labels)
        }
        
        # 计算轮廓系数
        silhouette_overall, silhouette_clusters = self.calculate_silhouette()
        results['silhouette'] = {
            'overall': silhouette_overall,
            'per_cluster': silhouette_clusters
        }
        
        # 计算CH指数
        results['calinski_harabasz'] = self.calculate_ch_score()
        
        # 计算簇内距离
        results['intra_cluster_distances'] = self.calculate_intra_cluster_distances()
        
        # 计算簇间距离
        results['inter_cluster_distances'] = self.calculate_inter_cluster_distances()
        
        # 计算Davies-Bouldin指数
        results['davies_bouldin'] = self.calculate_davies_bouldin()
        
        return results
        
    def visualize_evaluation(self, save_path='visualization/evaluation'):
        """可视化评估结果"""
        os.makedirs(save_path, exist_ok=True)
        timestamp = time.strftime("%Y%m%d_%H%M%S")
        
        # 1. 相似性矩阵可视化
        plt.figure(figsize=(12, 10))
        similarity_matrix = 1 / (1 + self.distance_matrix)  # 将距离转换为相似度
        plt.imshow(similarity_matrix, cmap='viridis')
        plt.colorbar(label='相似度')
        plt.title('样本相似性矩阵')
        plt.xlabel('样本索引')
        plt.ylabel('样本索引')
        plt.savefig(f'{save_path}/similarity_matrix_{timestamp}.png')
        plt.close()
        
        # 2. 聚类结果散点图
        plt.figure(figsize=(12, 10))
        unique_labels = np.unique(self.labels)
        colors = plt.cm.rainbow(np.linspace(0, 1, len(unique_labels)))
        
        for label, color in zip(unique_labels, colors):
            if label == -1:
                color = 'gray'
            mask = (self.labels == label)
            plt.scatter(self.X[mask, 0], self.X[mask, 1],
                       c=[color],
                       label=f'簇 {label}' if label != -1 else '噪声点',
                       alpha=0.6)
        
        plt.title('DBSCAN聚类结果')
        plt.legend()
        plt.grid(True)
        plt.savefig(f'{save_path}/clustering_result_{timestamp}.png')
        plt.close()
        
        # 3. 轮廓系数分布
        plt.figure(figsize=(12, 6))
        _, cluster_scores = self.calculate_silhouette()
        
        if cluster_scores:
            plt.bar(range(len(cluster_scores)), 
                   list(cluster_scores.values()),
                   tick_label=[f'簇 {k}' for k in cluster_scores.keys()])
            plt.title('各簇的轮廓系数分布')
            plt.xlabel('簇')
            plt.ylabel('轮廓系数')
            plt.grid(True, axis='y')
            plt.savefig(f'{save_path}/silhouette_scores_{timestamp}.png')
            plt.close()
        
        # 4. 簇间距离热力图
        plt.figure(figsize=(12, 10))
        inter_distances = self.calculate_inter_cluster_distances()
        
        if inter_distances:
            n_clusters = len(self.unique_labels)
            distance_matrix = np.zeros((n_clusters, n_clusters))
            
            for i, label1 in enumerate(self.unique_labels):
                for j, label2 in enumerate(self.unique_labels):
                    if label1 != label2:
                        distance_matrix[i, j] = inter_distances[label1][label2]
            
            plt.imshow(distance_matrix, cmap='YlOrRd')
            plt.colorbar(label='簇间距离')
            plt.xticks(range(n_clusters), 
                      [f'簇 {k}' for k in self.unique_labels], rotation=45)
            plt.yticks(range(n_clusters), 
                      [f'簇 {k}' for k in self.unique_labels])
            plt.title('簇间距离矩阵')
            plt.tight_layout()
            plt.savefig(f'{save_path}/cluster_distance_matrix_{timestamp}.png')
            plt.close()

def main():
    try:
        # 设置随机种子
        np.random.seed(42)
        
        # 生成数据
        logging.info("生成复杂数据集...")
        data_generator = DataGenerator()
        X = data_generator.generate_complex_dataset(random_state=42)
        
        # 创建并训练模型
        logging.info("初始化并训练DBSCAN模型...")
        dbscan = DBSCAN(eps=0.4, min_samples=5)
        dbscan.fit(X)
        
        # 获取性能统计
        stats = dbscan.get_performance_stats()
        logging.info(f"聚类完成！发现 {stats['n_clusters']} 个簇，"
                    f"{stats['n_noise']} 个噪声点")
        logging.info(f"执行时间: {stats['execution_time']:.2f} 秒")
        
        # 评估结果
        logging.info("评估聚类结果...")
        evaluator = ClusterEvaluator(X, dbscan.labels)
        evaluation_results = evaluator.evaluate()
        
        # 生成可视化结果
        logging.info("生成评估可视化结果...")
        evaluator.visualize_evaluation()
        
        # 保存结果
        save_results(dbscan, stats, evaluation_results)
        
    except Exception as e:
        logging.error(f"程序执行出错: {str(e)}")
        raise

def save_results(
    model: DBSCAN,
    stats: Dict,
    evaluation_results: Dict,
    save_dir: str = 'results'
) -> None:
    """保存实验结果"""
    os.makedirs(save_dir, exist_ok=True)
    
    # 保存参数和统计信息
    with open(f'{save_dir}/results.txt', 'w') as f:
        f.write("模型参数:\n")
        for k, v in model.get_params().items():
            f.write(f"{k}: {v}\n")
            
        f.write("\n性能统计:\n")
        for k, v in stats.items():
            f.write(f"{k}: {v}\n")
            
        f.write("\n评估结果:\n")
        for k, v in evaluation_results.items():
            f.write(f"{k}: {v}\n")

if __name__ == "__main__":
    main()
