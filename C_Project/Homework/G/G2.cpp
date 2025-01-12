//假设图采用邻接矩阵存储，设计非递归算法，实现图的深度遍历。给出完整程序。
#include <iostream>
#include <vector>
#include <stack>

using namespace std;

void dfs_non_recursive(const vector<vector<int>>& graph, int start) {
  int n = graph.size();
  vector<bool> visited(n, false); // 记录节点是否被访问
  stack<int> s; // 使用栈模拟递归

  s.push(start);
  visited[start] = true;

  while (!s.empty()) {
    int u = s.top();
    s.pop();
    cout << u << " "; // 访问节点

    // 遍历 u 的邻接节点，将未访问的节点入栈
    for (int v = n - 1; v >= 0; --v) {
      if (graph[u][v] == 1 && !visited[v]) {
        s.push(v);
        visited[v] = true;
      }
    }
  }
}

int main() {
  // 示例图的邻接矩阵
  //0->1->2;
  //1->0->3;
  //2->0->3;
  //3->1->2;
  vector<vector<int>> graph = {
    {0, 1, 1, 0},
    {1, 0, 0, 1},
    {1, 0, 0, 1},
    {0, 1, 1, 0}
  };

  // 从节点 0 开始深度优先遍历
  dfs_non_recursive(graph, 0);

  return 0;
}