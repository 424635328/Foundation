// P8673 [蓝桥杯 2018 国 C] 迷宫与陷阱
#include <bits/stdc++.h>

using namespace std;
int n, k;
char ma[1005][1005];
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1}; // 四个方向
int vis[1005][1005];
struct node
{
    int x, y, inv, step;
};
int main()
{
    cin >> n >> k;
    queue<node> q;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> ma[i][j];
            vis[i][j] = -1;
        }
    }
    node t;
    t.x = 0;
    t.y = 0;
    t.inv = 0;
    t.step = 0;
    q.push(t);
    vis[0][0] = 0;
    while (!q.empty())
    {
        t = q.front();
        q.pop();
        if (t.x == n - 1 && t.y == n - 1)
        {
            cout << t.step;
            return 0;
        }
        node p;
        for (int i = 0; i < 4; i++)
        {
            int fx, fy;
            fx = t.x + dx[i];
            fy = t.y + dy[i];
            if (ma[fx][fy] == 'X' && t.inv == 0)
                continue;
            if (ma[fx][fy] == '#')
                continue;
            p.inv = max(0, t.inv - 1);
            if (ma[fx][fy] == '%')
                p.inv = k;
            if (fx >= 0 && fy >= 0 && fx < n && fy < n&&vis[fx][fy]<p.inv){
                p.x=fx;
                p.y=fy;
                vis[fx][fy]=p.inv;
                p.step=t.step+1;
                q.push(p);
            }
        }
    }
    cout<<"-1";
    return 0;
}