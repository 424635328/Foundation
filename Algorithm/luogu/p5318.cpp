// P5318 【深基18.例3】查找文献
#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>

using namespace std;

// 邻接表存储图
vector<vector<int>> graph;
set<int> visited;

// 深度优先搜索
void dfs(int node) {
    visited.insert(node);
    cout << node << " ";
    for (int neighbor : graph[node]) {
        if (!visited.count(neighbor)) {
            dfs(neighbor);
        }
    }
}

// 广度优先搜索
void bfs(int start) {
    queue<int> q;
    q.push(start);
    visited.insert(start);

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        cout << node << " ";

        for (int neighbor : graph[node]) {
            if (!visited.count(neighbor)) {
                visited.insert(neighbor);
                q.push(neighbor);
            }
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    // 初始化邻接表和 visited 集合
    graph.resize(n + 1);
    visited.clear();

    // 读取边
    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        graph[x].push_back(y);
    }

    // 对每个节点的邻居进行排序，确保访问编号较小的节点
    for (int i = 1; i <= n; ++i) {
        sort(graph[i].begin(), graph[i].end());
    }

    // 深度优先搜索
    dfs(1);
    cout << endl;

    // 清空 visited 集合，为 BFS 做准备
    visited.clear();

    // 广度优先搜索
    bfs(1);
    cout << endl;

    return 0;
}