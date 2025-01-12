// 设计一个算法，通过一趟遍历，将链表中所有结点的链接方向逆转，且仍利用原表的存储空间。
#include <stdio.h>
#include <stdlib.h>
struct ListNode
{
    int val;
    struct ListNode *next;
};

// 逆转
struct ListNode *reversion(struct ListNode **head)
{
    struct ListNode *p = NULL;
    struct ListNode *curr = *head;
    struct ListNode *next = NULL;
    while (curr != NULL)
    {
        next = curr->next;
        curr->next = p;
        p = curr;
        curr = next;
    }
    return p;
}

// 打印
void printList(struct ListNode *head)
{
    while (head)
    {
        printf("%d ", head->val);
        head = head->next;
    }
    printf("\n");
}

int main()
{
    ListNode *head = NULL;
    int val;
    struct ListNode *dummy = (struct ListNode *)malloc(sizeof(struct ListNode));
    dummy->next = NULL;
    head = dummy;
    printf("请输入一串整数(输入-1结束):");
    while (scanf("%d", &val), val != -1)
    {

        ListNode *newNode = (ListNode *)malloc(sizeof(ListNode));
        newNode->val = val;
        newNode->next = NULL;
        dummy->next = newNode;
        dummy = newNode;
    }
    printf("逆转后:");
    printList(reversion(&head->next));
    return 0;
}