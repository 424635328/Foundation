// P4779 【模板】单源最短路径（标准版）
#include <bits/stdc++.h>
using namespace std;

#define MAX_N 100005 // 最大点数

int n, m, s;
vector<vector<pair<int, int>>> graph(MAX_N + 1);
int dist[MAX_N + 1];
bool visited[MAX_N + 1];

void dijkstra(int start) {
    // 初始化
    for (int i = 1; i <= n; i++) {
        dist[i] = INT_MAX;
        visited[i] = false;
    }
    dist[start] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; 
    pq.push({0, start});

    while (!pq.empty()) {
        int u = pq.top().second; 
        pq.pop();

        if (visited[u]) continue;
        visited[u] = true;

        // 更新 u 的邻接点距离
        for (auto& edge : graph[u]) {
            int v = edge.first;
            int weight = edge.second;
            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }
}

int main() {
    cin >> n >> m >> s;

    // 初始化邻接表
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
    }

    dijkstra(s);

    for (int i = 1; i <= n; i++) {
        cout << dist[i] << " ";
    }

    return 0;
}