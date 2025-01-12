// 采用循环链表存储约瑟夫问题,假设初始人数为8,从序号1开始报到,报到3就从节点中删除.每次发生删除后,下一个人从1开始报到.算法要求输出每一次删除的人员序号.
#include <stdio.h>
#include <stdlib.h>
typedef struct listnode
{
    int val;
    struct listnode *next;
} listnode;
int main()
{
    struct listnode *head = NULL;
    struct listnode *dummy = NULL;
    for (int i = 0; i < 8; i++)
    {
        listnode *newnode = (listnode *)malloc(sizeof(listnode));
        newnode->next = NULL;
        newnode->val = i + 1;
        if (head == NULL)
        {
            head = newnode;
            dummy = newnode;
        }
        dummy->next = newnode;
        dummy = dummy->next;
    }
    dummy->next = head; // 形成循环链表
    int i = 1;
    while (head->next != head)
    {
        head = head->next;
        i++;
        if (!(i % 2)) // 报数到3，所以只需要移动两次
        {
            printf("删除了%d号 \n", head->next->val);
            head->next = head->next->next;
        }
    }
    printf("剩下了%d号 ", head->val);
    head->next=NULL;
    free(head);
    return 0;
}