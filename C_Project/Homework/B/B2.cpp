//设计一个算法，通过一趟遍历在单链表中确定值最大的结点。
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

//添加
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
//求值
struct ListNode* MaxNode(struct ListNode* head){
    // 检查链表是否为空
    if(head == NULL) {
        printf("链表为空\n");
        return NULL;  
    }
    struct ListNode* maxNode = head;  
    int max = head->val;  
    while(head != NULL){  // 遍历整个链表，包括最后一个节点
        if(head->val > max){
            max = head->val;
            maxNode = head;
        }
        head = head->next;
    }
    return maxNode;
}


int main(){
    ListNode *head = NULL;
    int val;
    printf("请输入一串整数(输入-1结束):");
    while (scanf("%d", &val), val != -1)
    {
        append(&head, val);
    }
    ListNode *maxNode = MaxNode(head);
    if(maxNode != NULL) {
        printf("链表中值最大的节点的值是：%d\n", maxNode->val);
    } else {
        printf("链表为空\n");
    }
    return 0;
    

}