#include <stdio.h>
#include <stdlib.h>

void bestFitDecreasing(int s[], int n, int c)
{
    int *bins = (int *)calloc(n, sizeof(int)); // 初始化箱子状态
    int binsUsed = 0;                          // 记录使用的箱子数
    int i, j, bestIndex;

    // 先对物品按大小降序排序
    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (s[i] < s[j])
            {
                int temp = s[i];
                s[i] = s[j];
                s[j] = temp;
            }
        }
    }
    printf("排序后的物品顺序:");
    for (i = 0; i < n; i++)
    {
        printf("%d ", s[i]);
    }
    printf("\n");
    // 遍历物品并尝试放入箱子
    for (i = 0; i < n; i++)
    {
        bestIndex = -1;       // 记录最佳箱子的索引
        int bestDiff = c + 1; // 记录最佳剩余空间差，初始化为比箱子容量还大的值

        // 查找最佳箱子
        for (j = 0; j < binsUsed; j++)
        {
            int diff = c - bins[j] - s[i];
            if (diff >= 0 && diff < bestDiff)
            {
                bestDiff = diff;
                bestIndex = j;
            }
        }

        if (bestIndex != -1)
        {                            // 如果找到了最佳箱子
            bins[bestIndex] += s[i]; // 放入物品
            printf("第%d个物品放在第%d个箱子\n", i + 1, bestIndex + 1);
        }
        else
        { // 否则开新箱子
            bins[binsUsed++] = s[i];
            printf("第%d个物品放在第%d个箱子\n", i + 1, binsUsed);
        }
    }

    // 输出结果
    printf("需要 %d个箱子\n", binsUsed);
    free(bins);
}

int main()
{
    int s[] = {3, 2, 5, 1, 4};        // 物品大小
    int n = sizeof(s) / sizeof(s[0]); // 物品数量
    int c = 6;                        // 箱子容量
    bestFitDecreasing(s, n, c);
    return 0;
}