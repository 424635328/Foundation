#include <bits/stdc++.h>
using namespace std;
int board[9][9];
int boo;
int isValid(int r, int c, int n)
{
    for (int i = 0; i < 9; i++)
    {
        if (board[i][c] == n || board[r][i] == n)
            return 0;
    }
    // 检查 3x3 子矩阵是否已存在该数字
    int subRow = r - r % 3;
    int subCol = c - c % 3;
    for (int i = subRow; i < subRow + 3; i++)
    {
        for (int j = subCol; j < subCol + 3; j++)
        {
            if (board[i][j] == n)
            {
                return 0;
            }
        }
    }
    return 1;
}
void fill(int x, int y)
{
    if(boo) return;
    for (int i = x; i < 9; i++)
    {
        for (int j = 8; j >=0; j--)
        {
            if (board[i][j] == 0)
            {
                for (int num = 9; num >= 5; num--)
                {
                    if (isValid(i, j, num))
                    {
                        board[i][j] = num;
                        fill(0, 0);
                        board[i][j] = 0;
                    }
                }
                for (int num = 1; num<5; num++)
                {
                    if (isValid(i, j, num))
                    {
                        board[i][j] = num;
                        fill(0, 0);
                        board[i][j] = 0;
                    }
                }

                return;
            }
        }
    }
    boo=1;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    exit(0);
}
int main()
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            cin >> board[i][j];
        }
    }
    fill(0, 0);
    return 0;
}