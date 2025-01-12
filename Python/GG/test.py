import numpy as np
import matplotlib.pylab as plt
import sklearn.cluster as Meanshift
import scipy.spatial.distance as cdist
np.random.seed(42)
n_sample=150
n_features=2
X=np.random.randn(n_sample,n_features)

X=np.vstack([X,np.random.randn(50,2)+np.array([5,5])])
X=np.vstack([X,np.random.randn(50,2)+np.array([-5,-5])])
meanshift=Meanshift.MeanShift(bandwidth=2)
meanshift.fit(X)
labels=meanshift.labels_
cluster_centers=meanshift.cluster_centers_

if -1 in labels:
    noise_idx=np.where(labels==-1)[0]
    distances=cdist(X[noise_idx],cluster_centers)
    labels[noise_idx]=np.argmin(distances,axis=1)

plt.scatter(X[:,0],X[:,1],c=labels,cmap='viridis',marker='o')
plt.scatter(cluster_centers[:,0],cluster_centers[:,1],c='red',marker='x',s=200,alpha=0.75)

for i in range(len(cluster_centers)):
    for j in range(i+1,len(cluster_centers)):
            plt.plot([cluster_centers[i][0],cluster_centers[j][0]],[cluster_centers[i][1],cluster_centers[j][1]],'k--',alpha=0.5)
plt.title('Mean Shift Clustering')
plt.xlabel('Feature 1')
plt.ylabel('Feature 2')
plt.show()