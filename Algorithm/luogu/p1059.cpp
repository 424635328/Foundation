//P1059 [NOIP2006 普及组] 明明的随机数

#include <stdio.h>
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
void sort(int *a, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (a[i] > a[j])
            {
                swap(&a[i], &a[j]);
            }
            if (a[i] == a[j])
            {
                a[j] = 0;
            }
        }
    }
}
void check(int *a, int size)
{
    sort(a, size);
    int flag = 0;
    for (int i = 0; i < size; i++)
    {
        if (a[i] != 0)
            flag++;
    }
    printf("%d\n",flag);
    for (int i = 0; i < size; i++)
    {
        if (a[i] != 0)
            printf("%d ", a[i]);
    }
}
int main()
{
    int n;
    scanf("%d", &n);
    int a[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }
    check(a, n);
    return 0;
}