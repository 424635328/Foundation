// 假设图采用邻接矩阵存储，设计递归算法，实现图的深度遍历。给出完整程序。
#include <iostream>
#include <vector>

using namespace std;

// 图的邻接矩阵表示
vector<vector<int>> graph;
// 标记数组，记录节点是否被访问
vector<bool> visited;

void dfs(int u)
{
    visited[u] = true;
    cout << u << " ";
    for (int v = 0; v < graph.size(); ++v)
    {
        if (graph[u][v] == 1 && !visited[v])
        {
            dfs(v);
        }
    }
}

int main()
{
    int n = 4; // 节点数
    graph.resize(n, vector<int>(n, 0));
    visited.resize(n, false);

    // 示例图的邻接矩阵
    // 0->1->2;
    // 1->0->3;
    // 2->0->3;
    // 3->1->2;
    graph = {
        {0, 1, 1, 0},
        {1, 0, 0, 1},
        {1, 0, 0, 1},
        {0, 1, 1, 0}};

    // 从节点 0 开始进行深度优先遍历
    dfs(0);

    return 0;
}