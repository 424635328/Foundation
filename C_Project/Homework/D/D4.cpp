/*已知f为单链表的头指针，链表中存储的都是整数，试实现下列运算的递归算法：

1）求链表中的最大整数。

2）求链表中的结点个数。

3）求所有整数的平均值。*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct listnode
{
    int data;
    struct listnode *next;
} ListNode, *list;

void initlist(list *l)
{
    *l = (list)malloc(sizeof(ListNode));
    (*l)->next = NULL;
    ListNode *tail = *l;      
    for (int i = 0; i < 8; i++) // 生成8个随机数组成链
    {
        ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
        newNode->data = rand() % 10;
        newNode->next = NULL;
        tail->next = newNode;
        tail = newNode;
    }
}

void recursion(ListNode *l, int *max, int *flag, int *sum)
{
    if (l == NULL)
    {
        return;
    }
    if (*max < l->data)
    {
        *max = l->data;
    }
    (*flag)++;
    (*sum) += l->data;
    recursion(l->next, max, flag, sum); // 递归调用
}

int main()
{
    srand(time(NULL));
    int max = 0;
    list l = NULL;
    initlist(&l);
    ListNode *current = l->next; // 头节点不存储数据
    int flag = 0;
    int sum = 0;

    // 打印链表元素
    while (current)
    {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
    recursion(l->next, &max, &flag, &sum); // 从头节点的下一个节点开始
    float ave = (float)sum / flag;
    printf("1)Max:%d\n", max);
    printf("2)nodes:%d\n", flag);
    printf("3)sum:%d ave:%f\n", sum, ave);

    // 释放链表内存
    current = l;
    while (current)
    {
        ListNode *temp = current;
        current = current->next;
        free(temp);
    }//释放节点空间
    free(current);
    return 0;
}