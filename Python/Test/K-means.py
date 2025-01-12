import numpy as np
import matplotlib.pyplot as plt
from sklearn.datasets import make_blobs
import os
from tqdm import tqdm
import matplotlib.animation as animation

# 设置matplotlib支持中文显示
plt.rcParams['font.sans-serif'] = ['SimHei']
plt.rcParams['axes.unicode_minus'] = False

class KMeans:
    def __init__(self, n_clusters=3, max_iters=100, random_state=None):
        self.n_clusters = n_clusters
        self.max_iters = max_iters
        self.random_state = random_state
        self.centroids = None
        self.labels = None
        self.iteration_count = 0
        self.history = []  # 用于存储每一步的状态

    def _init_centroids(self, X):
        np.random.seed(self.random_state)
        random_idx = np.random.permutation(X.shape[0])[:self.n_clusters]
        self.centroids = X[random_idx]

    def _assign_clusters(self, X):
        distances = np.sqrt(((X - self.centroids[:, np.newaxis])**2).sum(axis=2))
        return np.argmin(distances, axis=0)

    def _update_centroids(self, X, labels):
        new_centroids = np.array([X[labels == k].mean(axis=0) 
                                 for k in range(self.n_clusters)])
        return new_centroids

    def fit(self, X):
        # 初始化聚类中心
        self._init_centroids(X)
        
        # 记录初始状态
        self.history.append({
            'centroids': self.centroids.copy(),
            'labels': np.zeros(X.shape[0]),
            'title': "初始化聚类中心"
        })
        
        prev_labels = None
        
        with tqdm(total=self.max_iters, desc="K-means聚类") as pbar:
            for i in range(self.max_iters):
                # 分配聚类标签
                self.labels = self._assign_clusters(X)
                self.history.append({
                    'centroids': self.centroids.copy(),
                    'labels': self.labels.copy(),
                    'title': f"第 {i+1} 次迭代: 分配样本到最近的聚类中心"
                })
                
                # 更新聚类中心
                new_centroids = self._update_centroids(X, self.labels)
                self.history.append({
                    'centroids': new_centroids.copy(),
                    'labels': self.labels.copy(),
                    'title': f"第 {i+1} 次迭代: 更新聚类中心位置"
                })
                
                # 检查是否收敛
                if np.all(self.labels == prev_labels):
                    print(f"\n算法在第 {i+1} 次迭代后收敛")
                    break
                    
                self.centroids = new_centroids
                prev_labels = self.labels.copy()
                self.iteration_count = i + 1
                pbar.update(1)
        
        return self

    def create_animation(self, X, output_file='kmeans_animation.gif'):
        """创建聚类过程的动画"""
        fig, ax = plt.subplots(figsize=(10, 6))
        
        def animate(frame):
            ax.clear()
            
            # 获取当前帧的状态
            state = self.history[frame]
            labels = state['labels']
            centroids = state['centroids']
            
            # 绘制数据点
            colors = plt.cm.rainbow(np.linspace(0, 1, self.n_clusters))
            for k, color in enumerate(colors):
                mask = (labels == k)
                ax.scatter(X[mask, 0], X[mask, 1], 
                          c=[color], 
                          label=f'簇 {k+1}',
                          alpha=0.6)

            # 绘制聚类中心
            ax.scatter(centroids[:, 0], centroids[:, 1],
                      c='black',
                      marker='x',
                      s=200,
                      linewidths=3,
                      label='聚类中心')
            
            ax.set_title(state['title'])
            ax.legend()
            ax.grid(True)
        
        # 创建动画
        anim = animation.FuncAnimation(
            fig, 
            animate,
            frames=len(self.history),
            interval=1000,  # 每帧之间的间隔（毫秒）
            repeat_delay=2000  # 重复播放前的延迟（毫秒）
        )
        
        # 保存动画
        os.makedirs('visualization/kmeans', exist_ok=True)
        anim.save(f'visualization/kmeans/{output_file}', 
                 writer='pillow', 
                 fps=1)
        plt.close()

def main():
    # 创建示例数据
    print("生成示例数据...")
    X, _ = make_blobs(n_samples=300, 
                      centers=3, 
                      cluster_std=0.60, 
                      random_state=0)
    
    # 创建并训练K-means模型
    print("\n初始化K-means聚类器...")
    kmeans = KMeans(n_clusters=3, 
                    max_iters=100, 
                    random_state=42)
    
    print("\n开始聚类...")
    kmeans.fit(X)
    
    print("\n创建动画...")
    kmeans.create_animation(X)
    
    print(f"\n聚类完成！总共迭代 {kmeans.iteration_count} 次")
    print("\n动画已保存在 visualization/kmeans 目录下")
    
    # 计算聚类评估指标
    inertia = np.sum((X - kmeans.centroids[kmeans.labels])**2)
    print(f"\n聚类惯性（总的平方距离）: {inertia:.2f}")

if __name__ == "__main__":
    main()
