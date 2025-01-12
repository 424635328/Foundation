//假设图采用邻接矩阵存储，设计算法，判断无向图中任意给定的两个顶点之间是否存在一条长度为K的简单路径。给出完整程序。
#include <stdio.h>
#include <stdbool.h>

#define MAX_VERTICES 100  // 最大顶点数

bool path(int graph[][MAX_VERTICES], int n, int start, int end, int k) {
  // 判别是否存在从 start 到 end 长度为 k 的路径

  if (k == 0) {
    return start == end; // 长度为 0，起点和终点必须相同
  }

  bool visited[MAX_VERTICES] = {false}; // 记录访问过的顶点
  visited[start] = true;

  for (int i = 0; i < n; ++i) {
    if (graph[start][i] && !visited[i]) {
      if (path(graph, n, i, end, k - 1)) {
        return true; // 递归查找长度为 k-1 的路径
      }
    }
  }

  return false; // 未找到路径
}

int main() {
  int n, k, start, end;
  int graph[MAX_VERTICES][MAX_VERTICES];

  // 输入顶点数、路径长度、起点和终点
  printf("请输入顶点数: ");
  scanf("%d", &n);
  printf("请输入路径长度 k: ");
  scanf("%d", &k);
  printf("请输入起点和终点 (0 ~ %d): ", n - 1);
  scanf("%d %d", &start, &end);

  // 输入邻接矩阵
  printf("请输入邻接矩阵:\n");
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      scanf("%d", &graph[i][j]);
    }
  }

  if (path(graph, n, start, end, k)) {
    printf("存在长度为 %d 的路径\n", k);
  } else {
    printf("不存在长度为 %d 的路径\n", k);
  }

  return 0;
}