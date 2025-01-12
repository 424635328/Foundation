// P1443 马的遍历
// 马走日
#include <bits/stdc++.h>
#include <stdio.h>
#include <queue>
using namespace std;
queue<int> qx, qy, qs;
int mp[401][401];
int vis[401][401];
int n, m, x, y;
int da[8] = {1, 2, 2, 1, -1, -2, -2, -1};
int db[8] = {-2, -1, 1, 2, 2, 1, -1, -2}; // 八个方向
int check(int x, int y)                   // 是否在棋盘内
{
    if (x < 0 || x >= n || y < 0 || y >= m)
        return 0;
    return 1;
}
void bfs()
{
    int a, b, step;
    while (qx.empty() == 0)
    {
        a = qx.front();
        b = qy.front();
        step = qs.front();
        qx.pop();
        qy.pop();
        qs.pop();
        mp[a][b] = step;
        for (int i = 0; i < 8; i++)
        {
            if (check(a + da[i], b + db[i]) && !vis[a + da[i]][b + db[i]])
            {
                vis[a + da[i]][b + db[i]] = 1;
                qx.push(a + da[i]);
                qy.push(b + db[i]);
                qs.push(step + 1);
            }
        }
    }
}
int main()
{
    cin >> n, cin >> m, cin >> x, cin >> y;
    memset(mp, -1, sizeof(mp)); // 初始化-1
    qx.push(x-1);
    qy.push(y-1);
    qs.push(0);
    vis[x-1][y-1] = 1;
    bfs();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (j == m - 1)
                cout << mp[i][j] << endl;
            else
                printf("%-5d", mp[i][j]);
        }
    }
    return 0;
}