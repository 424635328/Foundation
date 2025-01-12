// 使用两个栈实现一个队列，并写出入队、出队、判断空队的函数。
#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100

// 定义栈结构体
typedef struct
{
    int *base;
    int *top;
    int stacksize;
} stack;
void initstack(stack &s)
{
    s.base =(int*)malloc(MAXSIZE*sizeof(int));
    if (!s.base)
        exit(0);
    s.top = s.base;
    s.stacksize = MAXSIZE;
}
void push(stack &s, int num)
{
    if (s.top - s.base == s.stacksize)
        exit(0);
    *s.top++ = num;
}
int pop(stack &s)
{//直接返回栈顶元素
    if (s.top == s.base)
        exit(0);
    return *--s.top;
}
int stackempty(stack s){
    return s.base==s.top;
}
// 定义队列结构体
typedef struct
{
    stack s1; // 入队栈
    stack s2; // 出队栈
} queue;

// 初始化队列
void initqueue(queue &q)
{
    initstack(q.s1);
    initstack(q.s2);
}

// 入队函数
void enqueue(queue &q, int e)
{
    push(q.s1, e); 
}

// 出队函数
int dequeue(queue &q)
{
    if (stackempty(q.s2))
    { // 如果出队栈为空，则将入队栈的所有元素逆序转移到出队栈
        while (!stackempty(q.s1))
        {
            push(q.s2, pop(q.s1));
        }
    }
    return pop(q.s2); 
}

// 判断空队函数
int queueempty(queue &q)
{
    return stackempty(q.s1) && stackempty(q.s2); // 两个栈都为空时，队列为空
}

int main()
{
    queue q;
    initqueue(q);

    // 入队
    enqueue(q, 1);
    enqueue(q, 2);
    enqueue(q, 3);

    // 出队
    while (!queueempty(q))
    {
        printf("%d ", dequeue(q));
    }

    free(q.s1.base);
    free(q.s2.base);

    return 0;
}
