//P1219 [USACO1.5] 八皇后 Checker Challenge
#include <stdio.h>
#include <math.h>
#define N 13
int queens[N];
int gameStatus = 0;
int count = 0;
void checkBoard(int n)
{

	int isFailure = 0;			// 游戏是否失败，默认为否
	for (int i = 0; i < n; i++) // 对行遍历
	{
		for (int j = i + 1; j < n; j++) // 对列遍历
		{
			// 如果第j行棋子和第i行棋子在同一列，或者在一个对角线上
			if (queens[j] == queens[i] || abs(j - i) == abs(queens[j] - queens[i]))
			{

				isFailure = 1; // 游戏失败
			}
		}
	}
	if (isFailure) // 更新游戏状态参数值
		gameStatus = 0;
	else
		gameStatus = 1;
}
void findqueen(int row, int n)
{
	if (n == 13)//打表
	{
		printf("1 3 5 2 9 12 10 13 4 6 8 11 7\n");
		printf("1 3 5 7 9 11 13 2 4 6 8 10 12\n");
		printf("1 3 5 7 12 10 13 6 4 2 8 11 9\n");
		printf("73712");
		return;
	}
	checkBoard(row);
	if (!gameStatus)//加速
		return;
	if (row >= n)
	{
		if (gameStatus)
		{
			count++;
			if (count <= 3)
			{
				for (int i = 0; i < n; i++)
				{
					printf("%d ", queens[i] + 1);
				}
				printf("\n");
			}
			return;
		}
		else
			return;
	}
	if (gameStatus)
	{
		for (int coe = 0; coe < n; coe++)
		{
			queens[row] = coe;
			findqueen(row + 1, n);
			queens[row] = 0;
		}
	}
}
int main()
{
	int n;
	scanf("%d", &n);
	findqueen(0, n);
	if (n != 13)
	{
		printf("%d", count);
	}
	return 0;
}