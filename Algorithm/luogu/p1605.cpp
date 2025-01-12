// P1605 迷宫
/*1<=sx,sy<=5,0为边界*/
#include <iostream>
using namespace std;
int map[6][6];
int m, n, t, count;
int sx, sy, fx, fy;
void dfs(int x, int y)
{
    if(map[fx][fy]==2) return;
    if (x < 1 || x > n || y < 1 || y > n)
        return;
    if (x == fx && y == fy)
    {
        count++;
        return;
    }
    if (map[x][y] == 1 || map[x][y] == 2)
        return;
    map[x][y] = 1;
    dfs(x - 1, y);
    dfs(x + 1, y);
    dfs(x, y - 1);
    dfs(x, y + 1);
    map[x][y] = 0;
}
int main()
{
    cin >> m, cin >> n, cin >> t;
    cin >> sx, cin >> sy, cin >> fx, cin >> fy;
    for (int i = 0; i < t; i++)
    {
        int bx, by;
        cin >> bx, cin >> by;
        map[bx][by] = 2;
    }
    dfs(sx, sy);
    cout << count << endl;
    return 0;
}