#include <stdio.h>
#include <stdlib.h>
struct ListNode
{
    int val;
    struct ListNode *next;
};

// 创建
struct ListNode *createNode(int val)
{
    struct ListNode *newNode = (struct ListNode *)malloc(sizeof(struct ListNode));
    if (newNode == NULL)
    {
        exit(0);
    }
    newNode->val = val;
    newNode->next = NULL;
    return newNode;
}

// 添加
void append(ListNode **head, int val)
{
    ListNode *newNode = createNode(val);
    if (*head == NULL)
    {
        *head = newNode;
        return;
    }
    ListNode *last = *head;
    while (last->next != NULL)
    {
        last = last->next;
    }
    last->next = newNode;
}

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
    printf("请输入一串整数(输入-1结束):");
    while (scanf("%d", &val), val != -1)
    {
        append(&head, val);
    }
    printf("逆转后:");
    printList(reversion(&head));//^*传head地址值进reversion函数将改变指针head指向的位置
    //printList(head);
    return 0;
}