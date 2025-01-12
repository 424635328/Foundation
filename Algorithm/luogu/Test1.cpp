#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<int> s[100005];
int vis[100005];

void dfs(int x)
{
    if (vis[x])
        return;
    vis[x] = 1;
    cout<<x+1<<" ";
    for (int v : s[x])
        dfs(v);
}
void bfs()
{
    queue<int> q;
    q.push(0);
    while (!q.empty())
    {
        int x = q.front();
        q.pop();
        if (vis[x])
            continue;
        vis[x] = 1;
        cout<<x+1<<" ";
        for (int v : s[x])
            q.push(v);
    }
}

int main()
{
    cin >> n >> m;
    int j, k;
    for (int i = 0; i < m; i++)
    {
        cin >> j >> k;
        s[j - 1].push_back(k - 1); 
    }
    memset(vis, 0, sizeof(vis));
    dfs(0);
    cout << endl;
    memset(vis, 0, sizeof(vis));
    bfs();
    return 0;
}