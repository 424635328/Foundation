//P1162 填涂颜色
#include <stdio.h>
int a[101][101];
int used[101][101];
int m, n, count;
void dfs(int x, int y)
{
    if (a[x][y] || used[x][y])
        return;
    used[x][y] = 1;

    if (y + 1 < m)
        dfs(x, y + 1);
    if (x - 1 >= 0)
        dfs(x - 1, y);
    if (x + 1 < m)
        dfs(x + 1, y);
    if (y - 1 >= 0)
        dfs(x, y - 1);
}
int main()
{

    scanf("%d", &m);
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &a[i][j]);
        }
    }

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (!used[i][j] && !a[i][j] && (i == 0 || j == 0||i==m-1||j==m-1))
            {
                dfs(i, j);
            }
        }
    }
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (!used[i][j] && !a[i][j])
                printf("%d ", 2);
            else
                printf("%d ", a[i][j]);
        }
        printf("\n");
    }
    return 0;
}