// P3156 【深基15.例1】询问学号
#include <stdio.h>
#include<stdlib.h>
int main()
{
    int m=0, n=0,a=0;
    scanf("%d %d", &m, &n);
    long long arr[m];
    for (int i = 0; i < m; i++)
    {
        scanf("%lld", &arr[i]);
    }
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a);
        printf("%lld\n", arr[a-1]);
    }
    return 0;
}