// P2089 烤鸡
#include <stdio.h>
#include <stdbool.h>

#define NUM_INGREDIENTS 10

void backtrack(int *combination, int index, int target, int *count, int flag)
{
    if (index == NUM_INGREDIENTS)
    {
        if (target == 0)
        {
            if (flag)
            {
                for (int i = 0; i < NUM_INGREDIENTS; i++)
                {
                    printf("%d ", combination[i]);
                }
                printf("\n");
            }

            (*count)++;
        }
        return;
    }
    if (target >= 1)
    {
        combination[index] = 1;
        backtrack(combination, index + 1, target - 1, count, flag);
    }
    if (target >= 2)
    {
        combination[index] = 2;
        backtrack(combination, index + 1, target - 2, count, flag);
    }
    if (target >= 3)
    {
        combination[index] = 3;
        backtrack(combination, index + 1, target - 3, count, flag);
    }
}

int main()
{
    int n;
    scanf("%d", &n);
    int count = 0;
    int flag = 0;
    int combination[NUM_INGREDIENTS] = {0};
    backtrack(combination, 0, n, &count, flag);
    printf("%d\n", count);
    flag++;
    backtrack(combination, 0, n, &count, flag);
    return 0;
}