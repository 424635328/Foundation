#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100
typedef struct
{
    int *top;
    int *base;
    int stacksize;
} sqstack;
void initstack(sqstack &s)
{
    s.base = new int[MAXSIZE];
    if (!s.base)
        exit(0);
    s.top = s.base;
    s.stacksize = MAXSIZE;
}
void push(sqstack &s, int num)
{
    if (s.top - s.base == s.stacksize)
        exit(0);
    *s.top++ = num;
}
void pop(sqstack &s, int &num)
{
    if (s.top == s.base)
        exit(0);
    num = *--s.top;
}
int gettop(sqstack s)
{
    if (s.top != s.base)
        return *(s.top - 1);
}
char H(int val)
{
    if (val < 10)
        return '0' + val;
    else
        return 'A' + val - 10;
}
void DTH(int n)
{
    sqstack s;
    initstack(s);
    while (n > 0)
    {
        push(s, n % 16);
        n /= 16;
    }
    while (s.top != s.base)
    {
        printf("%c", H(gettop(s)));
        pop(s, *s.top);
    }
}
int main()
{
    printf("请输入一个十进制整数:\n");
    int n = 0;
    scanf("%d", &n);
    DTH(n);
    return 0;
}