// P1028 [NOIP2001 普及组] 数的计算
#include <stdio.h>
long long arr[1001];
int ma(int n)
{
    if (n == 1)
        return n;
    if (arr[n])
        return arr[n];
    arr[n] = 1;
    for (int i = 1; i <= n / 2; ++i)
    {
        arr[n] += ma(i);
    }
    return arr[n];
}
int main()
{
    int n;
    scanf("%d", &n);
    int flag = 1;

    printf("%d", ma(n));
    return 0;
}