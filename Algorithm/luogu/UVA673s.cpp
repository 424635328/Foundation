// 平衡的括号 Parentheses Balance
#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
using namespace std;
#define MAXSIZE 100
typedef struct
{
    char *top;
    char *base;
    int stacksize;
} sqstack;
void initstack(sqstack &s)
{
    s.base = (char *)malloc(MAXSIZE * sizeof(char));
    if (!s.base)
        exit(0);
    s.top = s.base;
    s.stacksize = MAXSIZE;
}
void push(sqstack &s, char num)
{
    if (s.top - s.base == s.stacksize)
        exit(0);
    *s.top++ = num;
}
void pop(sqstack &s, char &num)
{
    if (s.top == s.base)
        exit(0);
    num = *--s.top;
}
char gettop(sqstack s)
{
    if (s.top != s.base)
        return *(s.top - 1);
}
// 判断运算符优先级
char precede(char a, char b)
{
    if (a == '#')
    {
        return '<';
    }
    if (a == '[')
    {
        if (b == ']')
        {
            return '=';
        }
        else
        {
            return '<';
        }
    }
    if (a == '(')
    {
        if (b == ')')
        {
            return '=';
        }
        else
        {
            return '<';
        }
    }
    if (a == ')' || a == ']')
    {
        return '>';
    }
}
// 字符判定
int in(char ch)
{
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '#' || ch == '(' || ch == ')' || ch == '[' || ch == ']';
}
void check(sqstack opnd, string s)
{
    int j = s.size();
    int i = 0;
    char ch, x;
    push(opnd, '#');
    ch = s[i++];
    while (i <= j)
    {
        while (ch == ' ')
        {
            ch = s[i++];
            if (i > j)
            {

                break;
            }
        }
        if (i > j)
            break;
        char c = precede(gettop(opnd), ch);
        switch (c)
        {
        case '<':
            push(opnd, ch);
            ch = s[i++];
            break;
        case '=':
            pop(opnd, x);
            ch = s[i++];
            break;
        case '>':
            printf("No");
            return;
        }
    }
    if (gettop(opnd) == '#')
    {
        printf("Yes");
    }
    else
        printf("No");
}
int main()
{
    sqstack opnd;

    int n;
    scanf("%d", &n);
    getchar();
    string s[100];
    for (int i = 0; i < n; i++)
    {
        initstack(opnd);
        getline(cin, s[i]);
    }
    for (int i = 0; i < n; i++)
    {
        check(opnd, s[i]);
        printf("\n");
    }
    return 0;
}