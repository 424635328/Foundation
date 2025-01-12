import matplotlib.pyplot as plt
import numpy as np
import matplotlib.animation as animation

# 物品大小数组
s = [40, 30, 20, 10, 15, 25, 5, 35, 10, 20, 30, 15, 25, 35, 10, 20, 30, 15, 25, 35]
# 箱子容量
c = 50
# 物品数量
n = len(s)

# 回溯算法函数
def Backtracking(s, i):
    # 全局变量
    global bestNum, curNum, curC

    # 所有物品都已考虑时，更新最少箱子数量
    if i == n:
        if curNum < bestNum:
            bestNum = curNum
        return

    # 遍历当前使用的箱子
    for j in range(curNum):
        # 如果当前箱子剩余容量足够容纳当前物品
        if curC[j] >= s[i]:
            # 将物品放入当前箱子，并递归搜索下一物品
            curC[j] -= s[i]
            Backtracking(s, i + 1)
            # 恢复当前箱子状态
            curC[j] += s[i]

    # 如果当前使用的箱子数量小于最少箱子数量
    if curNum < bestNum:
        # 将当前物品放入一个新的箱子，并递归搜索下一物品
        curC[curNum] = c - s[i]
        curNum += 1
        Backtracking(s, i + 1)
        curNum -= 1

# 初始化变量
bestNum = n
curNum = 0
curC = [c] * n

# 执行回溯算法
Backtracking(s, 0)

# 可视化过程
fig, ax = plt.subplots(figsize=(10, 6))

# 箱子颜色
colors = ['#ff0000', '#00ff00', '#0000ff', '#ffff00', '#ff00ff', '#00ffff']

# 箱子位置和大小
box_positions = []
box_sizes = []

# 跟踪当前使用的箱子
current_boxes = []

# 记录每个箱子的物品
box_items = [[] for _ in range(bestNum)]

# 遍历物品，并将它们放入箱子
for i, item_size in enumerate(s):
    # 找到可以容纳当前物品的箱子
    for j in range(bestNum):
        if curC[j] >= item_size:
            # 将物品放入箱子
            curC[j] -= item_size
            box_items[j].append(item_size)
            # 更新箱子位置和大小
            box_positions.append(j)
            box_sizes.append(item_size)
            # 更新当前使用的箱子
            current_boxes.append(j)
            break

# 初始化绘图元素
bars = []
for i, box_size in enumerate(box_sizes):
    bar = ax.bar(box_positions[i], box_size, color=colors[i % len(colors)], label=f'Box {i+1}')
    bars.append(bar[0])  # Get the first bar object from the BarContainer

# 添加标签
labels = []
for i, box_item in enumerate(box_items):
    total_size = sum(box_item)
    label = ax.text(i, total_size, f'Items: {box_item}', ha='center', va='bottom')
    labels.append(label)

# 设置图表的标题和轴标签
ax.set_title(f'箱子装箱问题 (最佳解决方案：{bestNum} 个箱子)')
ax.set_xlabel('箱子编号')
ax.set_ylabel('箱子容量')
ax.legend()

# 设置图表布局
# plt.tight_layout()  # 移除这行代码，因为会导致中文显示错误

# 定义动画函数
def animate(i):
    # 更新每个箱子的高度
    for j, bar in enumerate(bars):
        bar.set_height(box_sizes[j])

    # 更新标签
    for j, label in enumerate(labels):
        label.set_text(f'Items: {box_items[j]}')

    # Return the updated bars and labels as a list
    return bars + labels 

# 创建动画
ani = animation.FuncAnimation(fig, animate, frames=len(box_sizes), interval=500, blit=True)

# 显示图表
plt.show()