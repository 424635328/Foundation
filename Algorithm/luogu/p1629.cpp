#include <bits/stdc++.h>
using namespace std;

#define MAX_N 1005 

int n, m;
vector<pair<int, int>> graph[MAX_N]; 
int dist[MAX_N];
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
void dijkstra(int start)
{
    for (int i = 1; i <= n; i++)
    {
        dist[i] = INT_MAX;
    }
    dist[start] = 0;


    pq.push({0, start});

    while (!pq.empty())
    {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (d > dist[u])
            continue; 

        for (auto &edge : graph[u])
        {
            int v = edge.first;
            int w = edge.second;
            if (dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
}
int djs(int str)
{ // 求出点str返回原点1的距离
    dijkstra(str);
    return dist[1];
}
int main()
{
    cin >> n >> m;

    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w}); 
    }

    int sum = 0;
    for(int i=2;i<=n;i++){
        sum+=djs(i);
    }
    dijkstra(1);
    for (int i = 1; i <= n; i++)
    {
        sum += dist[i];
    }
    cout << sum;

    return 0;
}