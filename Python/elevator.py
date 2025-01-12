import random
import heapq
from enum import Enum

class Direction(Enum):
    UP = 1
    DOWN = -1

class Elevator:
    def __init__(self, floors=30):
        """初始化电梯"""
        self.current_floor = random.randint(1, floors)
        self.direction = random.choice([Direction.UP, Direction.DOWN])
        self.up_requests = []  # 存储上行请求（最小堆）
        self.down_requests = []  # 存储下行请求（最大堆）
        self.high_freq_floors = {1, 15, 30}  # 高频楼层

    def add_request(self, floor):
        """添加请求到对应方向的堆"""
        if floor > self.current_floor:
            heapq.heappush(self.up_requests, floor)
        else:
            heapq.heappush(self.down_requests, -floor)  # 使用负数实现最大堆
        print(f"Request added for floor {floor}")

    def next_request(self):
        """根据当前方向获取下一个目标楼层"""
        if self.direction == Direction.UP and self.up_requests:
            return heapq.heappop(self.up_requests)
        elif self.direction == Direction.DOWN and self.down_requests:
            return -heapq.heappop(self.down_requests)

        # 切换方向并返回下一请求
        self.direction = Direction.DOWN if self.direction == Direction.UP else Direction.UP
        return self.next_request() if self.has_requests() else None

    def has_requests(self):
        """检查是否还有未处理的请求"""
        return bool(self.up_requests or self.down_requests)

    def move(self):
        """电梯开始运行并处理请求"""
        print(f"Starting at floor {self.current_floor}, direction: {self.direction.name}")
        while self.has_requests():
            next_floor = self.next_request()
            if next_floor is None:
                break
            print(f"Moving from {self.current_floor} to {next_floor}")
            self.current_floor = next_floor  # 更新当前楼层
        print("All requests completed. Elevator is idle.")

    def simulate_requests(self, num_requests=10):
        """模拟乘客请求"""
        for _ in range(num_requests):
            if random.random() < 0.3:
                floor = random.choice(list(self.high_freq_floors))
            else:
                floor = random.randint(1, 30)
            self.add_request(floor)

# 运行模拟
elevator = Elevator()
elevator.simulate_requests(num_requests=15)
elevator.move()
