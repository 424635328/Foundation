// P1451 求细胞数量
#include <stdio.h>
int a[101][101];
int used[101][101];
int m, n, count;
void dfs(int x, int y)
{
    if (!a[x][y] || used[x][y])
        return;
    used[x][y] = 1;
    if (y + 1 < n)
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

    scanf("%d %d", &m, &n);
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%1d", &a[i][j]);
        }
    }

    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (!used[i][j] && a[i][j])
            {
                 dfs(i, j);
                count++;
            }
            //         for(int i=0;i<m;i++){
            //     for(int j=0;j<n;j++){
            //         printf("%d",used[i][j]);
            //     }
            //     printf("\n");
            // }
        }
    }

    printf("%d", count);
    return 0;
}