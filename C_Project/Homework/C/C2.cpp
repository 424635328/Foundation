// 使用两个队列实现一个栈,并写出入栈、出栈、得到栈顶元素和判断空栈的函数。
#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100
typedef struct
{
    int *base;
    int front;
    int rear;
} queue;
void initQueue(queue &q)
{
    q.base = (int *)malloc(MAXSIZE * sizeof(int));
    q.front = q.rear = 0;
}

int isEmpty(queue &q)
{
    return q.front == q.rear;
}
//入队
void enqueue(queue &q, int x)
{
    if ((q.rear + 1) % MAXSIZE == q.front)
    {
        printf("Queue is full.\n");
        return;
    }
    q.base[q.rear] = x;
    q.rear = (q.rear + 1) % MAXSIZE;
}
//出队
int dequeue(queue &q)
{
    if (isEmpty(q))
    {
        printf("Queue is empty.\n");
        return -1;
    }
    int x = q.base[q.front];
    q.front = (q.front + 1) % MAXSIZE;
    return x;
}

typedef struct
{
    queue q1;
    queue q2;
} stack;

void initStack(stack &s)
{
    initQueue(s.q1);
    initQueue(s.q2);
}
// 入栈函数
void push(stack &s, int x)
{
    enqueue(s.q1, x);
}
// 出栈函数
int pop(stack &s)
{
    if (isEmpty(s.q1))
    {
        printf("Stack is empty.\n");
        return -1;
    }
    while ((s.q1.rear - s.q1.front + MAXSIZE) % MAXSIZE > 1)
    {
        enqueue(s.q2, dequeue(s.q1));
    }
    int x = dequeue(s.q1);
    queue temp = s.q1;
    s.q1 = s.q2;
    s.q2 = temp;
    return x;
}
// 得到栈顶元素函数
int top(stack &s)
{
    if (isEmpty(s.q1))
    {
        printf("Stack is empty.\n");
        return -1;
    }
    while ((s.q1.rear - s.q1.front + MAXSIZE) % MAXSIZE > 1)
    {
        enqueue(s.q2, dequeue(s.q1));
    }
    int x = s.q1.base[s.q1.front];
    enqueue(s.q2, dequeue(s.q1));
    queue temp = s.q1;
    s.q1 = s.q2;
    s.q2 = temp;
    return x;
}
// 判断空栈
int isEmptyStack(stack &s)
{
    if (isEmpty(s.q1) && isEmpty(s.q2))
    {
        return 1;
    }
    return 0;
}
int main()
{
    stack s;
    initStack(s);
    push(s, 1);
    push(s, 2);
    push(s, 3);
    while (!isEmptyStack(s))
    {
        printf("%d", pop(s));
    }
    return 0;
}