import numpy as np
import matplotlib.pyplot as plt
from sklearn.datasets import make_blobs
import os
from tqdm import tqdm
import matplotlib.animation as animation
from collections import defaultdict

# 设置matplotlib支持中文显示
plt.rcParams['font.sans-serif'] = ['SimHei']
plt.rcParams['axes.unicode_minus'] = False

class OPTICS:
    """
    OPTICS (Ordering Points To Identify the Clustering Structure)
    基于密度的排序点识别聚类结构算法
    
    特点：
    1. 可以发现任意形状的聚类
    2. 可以处理不同密度的簇
    3. 不需要预先指定聚类数量
    4. 生成可达性图来辅助理解聚类结构
    
    参数说明：
    - min_samples: 核心点的最小邻域样本数
    - max_eps: 最大邻域半径（可选）
    """
    
    def __init__(self, min_samples=5, max_eps=np.inf):
        self.min_samples = min_samples
        self.max_eps = max_eps
        self.ordered_points = []
        self.reachability = []
        self.core_distances = {}
        self.processed = set()
        self.history = []  # 用于存储每一步的状态
        
    def _calculate_core_distance(self, X, point_idx):
        """计算核心距离"""
        distances = np.sqrt(np.sum((X - X[point_idx]) ** 2, axis=1))
        sorted_distances = np.sort(distances)
        if len(sorted_distances) >= self.min_samples:
            return sorted_distances[self.min_samples - 1]
        return np.inf
    
    def _get_neighbors(self, X, point_idx):
        """获取邻域内的点"""
        distances = np.sqrt(np.sum((X - X[point_idx]) ** 2, axis=1))
        return np.where(distances <= self.max_eps)[0]
    
    def _update_seeds(self, X, seeds, point_idx, neighbors):
        """更新种子点集合"""
        core_dist = self.core_distances[point_idx]
        for neighbor in neighbors:
            if neighbor in self.processed:
                continue
                
            new_reach_dist = max(
                core_dist,
                np.sqrt(np.sum((X[point_idx] - X[neighbor]) ** 2))
            )
            
            if neighbor not in seeds:
                seeds[neighbor] = new_reach_dist
            else:
                seeds[neighbor] = min(seeds[neighbor], new_reach_dist)
    
    def fit(self, X):
        """训练OPTICS模型"""
        n_samples = X.shape[0]
        
        # 初始化状态
        self.history.append({
            'ordered_points': [],
            'reachability': [],
            'current_point': None,
            'seeds': {},
            'title': "初始状态"
        })
        
        # 计算所有点的核心距离
        for i in range(n_samples):
            self.core_distances[i] = self._calculate_core_distance(X, i)
        
        with tqdm(total=n_samples, desc="OPTICS聚类") as pbar:
            # 处理每个未处理的点
            for start_point in range(n_samples):
                if start_point in self.processed:
                    continue
                    
                # 获取邻域点
                seeds = {}
                neighbors = self._get_neighbors(X, start_point)
                self._update_seeds(X, seeds, start_point, neighbors)
                
                # 记录起始点
                self.processed.add(start_point)
                self.ordered_points.append(start_point)
                self.reachability.append(np.inf)
                
                # 记录当前状态
                self.history.append({
                    'ordered_points': self.ordered_points.copy(),
                    'reachability': self.reachability.copy(),
                    'current_point': start_point,
                    'seeds': seeds.copy(),
                    'title': f"处理起始点 {start_point}"
                })
                
                pbar.update(1)
                
                # 扩展密度可达的点
                while seeds:
                    # 获取可达性距离最小的点
                    next_point = min(seeds.items(), key=lambda x: x[1])[0]
                    reach_dist = seeds.pop(next_point)
                    
                    if next_point in self.processed:
                        continue
                        
                    # 处理下一个点
                    self.processed.add(next_point)
                    self.ordered_points.append(next_point)
                    self.reachability.append(reach_dist)
                    
                    # 如果是核心点，更新种子集合
                    if self.core_distances[next_point] <= self.max_eps:
                        neighbors = self._get_neighbors(X, next_point)
                        self._update_seeds(X, seeds, next_point, neighbors)
                    
                    # 记录当前状态
                    self.history.append({
                        'ordered_points': self.ordered_points.copy(),
                        'reachability': self.reachability.copy(),
                        'current_point': next_point,
                        'seeds': seeds.copy(),
                        'title': f"扩展点 {next_point}"
                    })
                    
                    pbar.update(1)
        
        return self
    
    def create_animation(self, X, output_file='optics_animation.gif'):
        """创建聚类过程的动画"""
        fig = plt.figure(figsize=(15, 8))
        gs = plt.GridSpec(2, 1, height_ratios=[2, 1])
        
        ax_scatter = fig.add_subplot(gs[0])
        ax_reach = fig.add_subplot(gs[1])
        
        def animate(frame):
            ax_scatter.clear()
            ax_reach.clear()
            
            # 获取当前帧的状态
            state = self.history[frame]
            ordered_points = state['ordered_points']
            reachability = state['reachability']
            current_point = state['current_point']
            
            # 绘制散点图
            ax_scatter.scatter(X[:, 0], X[:, 1], c='gray', alpha=0.5, label='未处理点')
            
            if ordered_points:
                # 绘制已处理的点
                processed_points = X[ordered_points]
                ax_scatter.scatter(processed_points[:, 0], processed_points[:, 1],
                                c='blue', alpha=0.6, label='已处理点')
            
            if current_point is not None:
                # 绘制当前点
                ax_scatter.scatter(X[current_point, 0], X[current_point, 1],
                                c='red', marker='*', s=200, label='当前点')
                
                # 绘制核心距离圆
                circle = plt.Circle(
                    (X[current_point, 0], X[current_point, 1]),
                    self.core_distances[current_point],
                    fill=False,
                    linestyle='--',
                    color='red',
                    alpha=0.3
                )
                ax_scatter.add_artist(circle)
            
            ax_scatter.set_title(state['title'])
            ax_scatter.legend()
            ax_scatter.grid(True)
            
            # 绘制可达性图
            if ordered_points:
                ax_reach.plot(range(len(reachability)), reachability, 'b-')
                ax_reach.scatter(range(len(reachability)), reachability, c='blue')
                if current_point is not None:
                    current_idx = ordered_points.index(current_point)
                    ax_reach.scatter(current_idx, reachability[current_idx],
                                  c='red', marker='*', s=200)
            
            ax_reach.set_xlabel('点的顺序')
            ax_reach.set_ylabel('可达性距离')
            ax_reach.grid(True)
            
            plt.tight_layout()
        
        # 创建动画
        anim = animation.FuncAnimation(
            fig, 
            animate,
            frames=len(self.history),
            interval=1000,
            repeat_delay=2000
        )
        
        # 保存动画
        os.makedirs('visualization/optics', exist_ok=True)
        anim.save(f'visualization/optics/{output_file}',
                 writer='pillow',
                 fps=60)
        plt.close()

def main():
    # 创建示例数据
    print("生成示例数据...")
    X, _ = make_blobs(n_samples=200, 
                      centers=3, 
                      cluster_std=[1.0, 2.0, 0.5],
                      random_state=42)
    
    # 创建并训练OPTICS模型
    print("\n初始化OPTICS聚类器...")
    optics = OPTICS(min_samples=5, max_eps=2.0)
    
    print("\n开始聚类...")
    optics.fit(X)
    
    print("\n创建动画...")
    optics.create_animation(X)
    
    print("\n聚类完成！")
    print(f"处理的点数量: {len(optics.ordered_points)}")
    print("\n动画已保存在 visualization/optics 目录下")

if __name__ == "__main__":
    main()
