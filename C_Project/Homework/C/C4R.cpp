// 设计算法，求解表达式：(1+(4+5*3)-4)+(6+8)的值.请同学们认真思考,那个运算符优先级的表格如何设计.
#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100
// 操作数栈
typedef struct
{
    int *top;
    int *base;
    int stacksize;
} opndstack;
// 操作符栈
typedef struct
{
    char *top;
    char *base;
    int stacksize;
} optrstack;
// 初始化栈
void initopndstack(opndstack &s)
{
    s.base = (int *)malloc(MAXSIZE * sizeof(int));
    if (!s.base)
        exit(0);
    s.top = s.base;
    s.stacksize = MAXSIZE;
}
void initoptrstack(optrstack &s)
{
    s.base = (char *)malloc(MAXSIZE * sizeof(char));
    if (!s.base)
        exit(0);
    s.top = s.base;
    s.stacksize = MAXSIZE;
}
// 入栈
void push(opndstack &s, int num)
{
    if (s.top - s.base == s.stacksize)
        exit(0);
    *s.top++ = num;
}
void pushc(optrstack &s, char theta)
{
    if (s.top - s.base == s.stacksize)
        exit(0);
    *s.top++ = theta;
}
// 出栈
void pop(opndstack &s, int &num)
{
    if (s.top == s.base)
        exit(0);
    num = *--s.top;
}
void popc(optrstack &s, char &theta)
{
    if (s.top == s.base)
        exit(0);
    theta = *--s.top;
}
// 取出栈顶元素
int gettop(opndstack s)
{
    if (s.top != s.base)
        return *(s.top - 1);
}
char gettopc(optrstack s)
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
int evaluate(opndstack &opnd, optrstack &optr)
{
    char expression[] = "(1+(4+5*3)-4)+(6+8)#";
    pushc(optr, '#');
    char ch;
    char theta;
    int a;
    int b;
    char x;
    int i = 0;
    
    ch = expression[i++];
    while (ch != '#' || gettopc(optr) != '#')
    {
        if (!in(ch))
        {
            ch = ch - '0'; // 将字符转换为整数
            push(opnd, ch);
            ch = expression[i++];
        }
        else
            switch (precede(gettopc(optr), ch))
            {
            case '<':
                pushc(optr, ch);
                ch = expression[i++];
                break;
            case '>':
                popc(optr, theta);
                pop(opnd, b);
                pop(opnd, a);
                push(opnd, operate(a, theta, b));
                break;
            case '=':
                popc(optr, x);
                 ch = expression[i++];
            default:
                break;
            }
    }
    return gettop(opnd);
}
int main()
{
    opndstack opnd;
    optrstack optr;
    initopndstack(opnd);
    initoptrstack(optr);
    printf("%d", evaluate(opnd, optr));
    return 0;
}