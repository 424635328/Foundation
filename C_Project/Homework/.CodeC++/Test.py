import random

def bin_packing_backtracking(items, capacity):
    """
    使用回溯算法解决箱子装载问题。

    参数：
        items: 物品大小数组
        capacity: 箱子容量

    返回值：
        一个元组，包含：
            - 使用的物品大小数组
            - 箱子装载情况（二维列表，每个子列表表示一个箱子的装载情况）
            - 箱子使用个数
    """

    # 初始化
    used_items = []
    bin_assignments = []
    bin_count = 0

    # 创建一个新的箱子
    def new_bin():
        nonlocal bin_count
        bin_count += 1
        bin_assignments.append([])

    # 回溯函数
    def backtrack(current_item):
        nonlocal used_items, bin_assignments
        # 所有物品都已分配
        if current_item == len(items):
            return True

        # 尝试将当前物品放入每个箱子
        for bin_index in range(bin_count):
            # 如果当前物品可以放入当前箱子
            if sum(bin_assignments[bin_index]) + items[current_item] <= capacity:
                # 放入当前箱子
                bin_assignments[bin_index].append(items[current_item])
                used_items.append(items[current_item])

                # 递归尝试下一件物品
                if backtrack(current_item + 1):
                    return True

                # 回溯：从当前箱子中移除当前物品
                bin_assignments[bin_index].pop()
                used_items.pop()

        # 如果当前物品不能放入任何箱子，创建一个新的箱子
        new_bin()
        bin_assignments[bin_count - 1].append(items[current_item])
        used_items.append(items[current_item])

        # 递归尝试下一件物品
        return backtrack(current_item + 1)

    # 开始回溯
    backtrack(0)

    # 返回结果
    return used_items, bin_assignments, bin_count

# 生成随机物品大小
items = [random.randint(0, 70) for _ in range(20)]
capacity = 100

# 使用回溯算法解决箱子装载问题
used_items, bin_assignments, bin_count = bin_packing_backtracking(items, capacity)

# 打印结果
print("物品大小：", used_items)
print("箱子装载情况：", bin_assignments)
print("箱子使用个数：", bin_count)
#回溯算法