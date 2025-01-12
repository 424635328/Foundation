import matplotlib.pyplot as plt
import random

# 箱子容量
bin_capacity = 10

# 生成随机物品
n = 200
object_sizes = [random.randint(1, bin_capacity) for _ in range(n)]

# 贪心算法实现最优装载
def first_fit(objects, bin_capacity):
    bins = []
    for obj in objects:
        placed = False
        for b in bins:
            if sum(b) + obj <= bin_capacity:
                b.append(obj)
                placed = True
                break
        if not placed:
            bins.append([obj])
    return bins

bins = first_fit(object_sizes, bin_capacity)

# 可视化
fig, ax = plt.subplots()
for i, b in enumerate(bins):
    ax.broken_barh([(sum(b[:j]), b[j]) for j in range(len(b))], (i * 10, 9), facecolors='tab:blue')

ax.set_xlabel('Bin Capacity')
ax.set_ylabel('Bins')
ax.set_title('Bin Packing Visualization')
plt.show()
