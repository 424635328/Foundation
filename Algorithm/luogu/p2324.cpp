//P2324 [SCOI2005] 骑士精神
#include <bits/stdc++.h>
using namespace std;
int ma[5][5];
const int goal[5][5] = {{1, 1, 1, 1, 1}, {0, 1, 1, 1, 1}, {0, 0, 2, 1, 1}, {0, 0, 0, 0, 1}, {0, 0, 0, 0, 0}};
int maxstep;
int t, starx, stary, acc;
int dx[] = {-2, -2, 2, 2, 1, 1, -1, -1};
int dy[] = {1, -1, 1, -1, 2, -2, 2, -2};
int eva()
{
    int count = 0;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (ma[i][j] != goal[i][j])
                count++;
        }
    }
    return count;
}
int check(int x, int y)
{
    if (x < 0 || x > 4 || y < 0 || y > 4)
        return 0;
    return 1;
}
void dfs(int step, int x, int y)
{
    if (step == maxstep)
    {
        if (!eva())
            acc = 1;
        return;
    }
    for (int i = 0; i < 8; i++)
    {
        int xx = x + dx[i];
        int yy = y + dy[i];
        if (!check(xx, yy))
            continue;
        swap(ma[x][y], ma[xx][yy]);
        if (eva() + step <= maxstep)
            dfs(step + 1, xx, yy);
        swap(ma[xx][yy], ma[x][y]);
    }
}
int main()
{
    cin >> t;
    char a;
    for (int k = 0; k < t; k++)
    {
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                cin >> a;
                if (a == '1')
                    ma[i][j] = 1;
                else if (a == '0')
                    ma[i][j] = 0;
                else
                {
                    ma[i][j] = 2;
                    starx = i;
                    stary = j;
                }
            }
        }
        if (!eva())
            cout << "0" << endl;
        for (maxstep = 1; maxstep <= 15; maxstep++)
        {
            dfs(0, starx, stary);
            if (acc)
            {
                cout << maxstep << endl;
                break;
            }
        }
        if (!acc)
        {
            cout << "-1" << endl;
        }
        acc = 0;
    }
    return 0;
}