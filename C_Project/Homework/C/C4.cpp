// 设计算法，求解表达式：(1+(4+5*3)-4)+(6+8)的值.请同学们认真思考,那个运算符优先级的表格如何设计.
#include <stdio.h>
#include <stdlib.h>
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
        if (b == '#')
        {
            return '=';
        }
        else
        {
            return '<';
        }
    }
    if (a == '+' || a == '-')
    {
        if (b == '+' || b == '-' || b == ')' || b == '#')
        { // 这种情况是栈顶优先级较高，返回 >
            return '>';
        }
        else
        {
            return '<';
        }
    }
    if (a == '*' || a == '/')
    {
        if (b == '(')
        {
            return '<';
        }
        else
        {
            return '>';
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
    if (a == ')')
    {
        return '>';
    }
}
// 字符判定
int in(char ch)
{
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '#' || ch == '(' || ch == ')';
}
// 进行二元计算
int operate(int a, char theta, int b)
{
    switch (theta)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
    {
        if (b != 0)
            return a / b;
        else
            printf("除数不能为0");
        return 0;
    }
    default:
        printf("运算符错误");
        return 0;
    }
}
char evaluate(sqstack &opnd, sqstack &optr)
{
    push(optr, '#');
    char ch;
    char theta;
    char a;
    char b;
    char x;
    int i = 0;
    char expression[] = "(1+(4+5*3)-4)+(6+8)#";
    ch = expression[i++];
    while (ch != '#' || gettop(optr) != '#')
    {
        if (!in(ch))
        {
            ch -= '0';
            push(opnd, (int)ch);
            ch = expression[i++];
        }
        else
            switch (precede(gettop(optr), ch))
            {
            case '<':
                push(optr, ch);
                ch = expression[i++];
                break;
            case '>':
                pop(optr, theta);
                pop(opnd, b);
                pop(opnd, a);
                push(opnd, operate(a, theta, b));
                break;
            case '=':
                pop(optr, x);
                ch = expression[i++];
            default:
                break;
            }
    }
    return gettop(opnd);
}
int main()
{
    sqstack opnd;
    sqstack optr;
    initstack(opnd);
    initstack(optr);
    printf("%d", evaluate(opnd, optr));
    return 0;
}