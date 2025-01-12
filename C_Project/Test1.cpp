//采用链表存储稀疏多项式非零项的系数及其指数,并实现两个稀疏多项式的加法运算.要求在算法执行过程中,,释放掉多余的节点空间.
#include<stdio.h>
#include<stdlib.h>
struct PolyNode{
    int coe;
    float exp;
    struct PolyNode* next;

};
struct PolyNode * createNode(int coe,float exp){
    PolyNode* newNode=(PolyNode*)malloc(sizeof(PolyNode));
    if(newNode==NULL){
        exit(0);

    }
    newNode->coe=coe;
    newNode->exp=exp;
    newNode->next=NULL;
    return newNode;
}
void printList(struct PolyNode *head)
{
    while (head)
    {
        printf("(%d,%f) ", head->coe,head->exp);
        head = head->next;
    }
    printf("\n");
}

struct PolyNode* add(PolyNode* n1,PolyNode* n2){
    PolyNode* n = createNode(0, 0); // 创建一个头节点
    PolyNode* cur = n; // 创建一个指针来跟踪结果链表的当前位置

    while(n1 && n2) {
        if(n1->exp == n2->exp) {
            n1->coe += n2->coe;
            if(n1->coe != 0) {
                cur->next = n1;
                cur = cur->next;
            }
            PolyNode *temp = n2;
            n1 = n1->next;
            n2 = n2->next;
            free(temp);
        } else if(n1->exp > n2->exp) {
            cur->next = n2;
            n2 = n2->next;
            cur = cur->next;
        } else {
            cur->next = n1;
            n1 = n1->next;
            cur = cur->next;
        }
    }

    if(n1) cur->next = n1;
    if(n2) cur->next = n2;

    PolyNode* temp = n;
    n = n->next;
    free(temp); // 释放头节点

    return n;
}
int main(){
    PolyNode* node1 = createNode(5, 3.000000);
    PolyNode* node2 = createNode(9, 6.600000);
    node1->next = createNode(5, 3.000000);
    node2->next = createNode(8, 6.600000);

    PolyNode* result = add(node1, node2);
    printList(result);

    // 释放结果链表的内存
    while(result){
        PolyNode* temp = result;
        result = result->next;
        free(temp);
    }

    return 0;
}