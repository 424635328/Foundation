// P5318 【深基18.例3】查找文献
#include <bits/stdc++.h>
using namespace std;
int n, m;
set<int> s[100005];
int vis[100005];
void dfs(int r)
{
    if (vis[r])
        return;
    vis[r] = 1;
    cout << r + 1 << " ";
    for (int i : s[r])
        dfs(i);
}
void bfs()
{
    queue<int> q;
    q.push(0);
    int x;
    while (!q.empty())
    {
         x = q.front();
        q.pop();
        if (vis[x])
            continue;
        cout << x+1 << " ";
        vis[x]=1;
        for (int i : s[x])
            q.push(i-1);
    }
    cout<<x+2;
}
int main()
{
    cin >> n, cin >> m;
    int j, k;
    for (int i = 0; i < m; i++)
    {
        cin >> j, cin >> k;
        s[j - 1].insert(k - 1);
    }
    memset(vis, 0, sizeof(vis));
    dfs(0);
    cout << endl;
    memset(vis,0,sizeof(vis));
    bfs();
    return 0;
}