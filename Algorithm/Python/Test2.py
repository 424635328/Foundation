import random
import math

def bin_packing_simulated_annealing(items, capacity, temperature=100, cooling_rate=0.95):
    """
    使用模拟退火算法解决箱子装载问题。

    参数：
        items: 物品大小数组
        capacity: 箱子容量
        temperature: 初始温度
        cooling_rate: 降温速率

    返回值：
        一个元组，包含：
            - 使用的物品大小数组
            - 箱子装载情况（二维列表，每个子列表表示一个箱子的装载情况）
            - 箱子使用个数
    """

    # 初始化解
    current_solution = random.sample(items, len(items))

    # 评估适应度函数
    def fitness(solution):
        bins = []
        current_bin = []
        bin_count = 0
        for item in solution:
            if sum(current_bin) + item <= capacity:
                current_bin.append(item)
            else:
                bins.append(current_bin)
                current_bin = [item]
                bin_count += 1
        bins.append(current_bin)
        return -bin_count  # 最小化箱子使用数量

    # 生成邻域解
    def generate_neighbor(solution):
        neighbor = solution.copy()
        index1 = random.randint(0, len(solution) - 1)
        index2 = random.randint(0, len(solution) - 1)
        neighbor[index1], neighbor[index2] = neighbor[index2], neighbor[index1]
        return neighbor

    # 模拟退火主循环
    while temperature > 1:
        # 生成邻域解
        neighbor_solution = generate_neighbor(current_solution)

        # 计算适应度差
        delta = fitness(neighbor_solution) - fitness(current_solution)

        # 接受概率
        if delta > 0 or random.random() < math.exp(delta / temperature):
            current_solution = neighbor_solution

        # 降温
        temperature *= cooling_rate

    # 解码结果
    used_items = current_solution
    bin_assignments = []
    current_bin = []
    bin_count = 0
    for item in used_items:
        if sum(current_bin) + item <= capacity:
            current_bin.append(item)
        else:
            bin_assignments.append(current_bin)
            current_bin = [item]
            bin_count += 1
    bin_assignments.append(current_bin)

    return used_items, bin_assignments, -fitness(current_solution)

# 生成随机物品大小
items = [random.randint(1, 60) for _ in range(500)]
capacity = 100

# 使用模拟退火算法解决箱子装载问题
used_items, bin_assignments, bin_count = bin_packing_simulated_annealing(items, capacity)

# 打印结果
print("物品大小：", used_items)
print("箱子装载情况：", bin_assignments)
print("箱子使用个数：", bin_count)
# 模拟退火