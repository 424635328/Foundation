//采用链表存储稀疏多项式非零项的系数及其指数,并实现两个稀疏多项式的加法运算.要求在算法执行过程中,,释放掉多余的节点空间.
#include <stdio.h>
#include <stdlib.h>

typedef struct PolyNode
{
    int coe;
    float exp;
    struct PolyNode *next;
} PolyNode;

PolyNode *createNode(int coe, float exp)
{
    PolyNode *newNode = (PolyNode *)malloc(sizeof(PolyNode));
    if (newNode == NULL)
    {
        exit(0);
    }
    newNode->coe = coe;
    newNode->exp = exp;
    newNode->next = NULL;
    return newNode;
}
void printList(PolyNode *head)
{
    while (head)
    {
        printf("(%d,%f) ", head->coe, head->exp);
        head = head->next;
    }
    printf("\n");
}

// 插入新的非零项到多项式
void insertNode(PolyNode **poly, int coe, float exp)
{
    if (coe == 0)
    {
        return;
    }
    PolyNode *newNode = createNode(coe, exp);
    PolyNode *current = *poly, *prev = NULL;

    // 查找插入位置
    while (current && current->exp < exp)
    {
        prev = current;
        current = current->next;
    }

    // 插入新节点
    if (current && current->exp == exp)
    {
        // 如果指数相同，合并系数
        current->coe += coe;
        free(newNode);
        if (current->coe == 0)
        {
            // 如果合并后系数为0，删除该节点
            if (prev)
            {
                prev->next = current->next;
            }
            else
            {
                *poly = current->next;
            }
            free(current);
        }
    }
    else
    {
        if (prev)
        {
            prev->next = newNode;
        }
        else
        {
            *poly = newNode;
        }
        newNode->next = current;
    }
}

// 多项式加法
PolyNode *addPolynomials(PolyNode *poly1, PolyNode *poly2)
{
    PolyNode *result = NULL;
    while (poly1 && poly2)
    {
        if (poly1->exp < poly2->exp)
        {
            insertNode(&result, poly2->coe, poly2->exp);
            poly2 = poly2->next;
        }
        else if (poly1->exp > poly2->exp)
        {
            insertNode(&result, poly1->coe, poly1->exp);
            poly1 = poly1->next;
        }
        else
        {
            insertNode(&result, poly1->coe + poly2->coe, poly1->exp);
            poly1 = poly1->next;
            poly2 = poly2->next;
        }
    }
    while (poly1)
    {
        insertNode(&result, poly1->coe, poly1->exp);
        poly1 = poly1->next;
    }
    while (poly2)
    {
        insertNode(&result, poly2->coe, poly2->exp);
        poly2 = poly2->next;
    }
    return result;
}

int main()
{
    PolyNode *node1 = createNode(6, 0.000000); // 一些具有代表性的例子
    PolyNode *node2 = createNode(9, 6.600000);
    node1->next = createNode(5, 32.000000);
    node2->next = createNode(8, 6.600000);
    node1->next->next = createNode(6, 31.00000);
    PolyNode *result = addPolynomials(node1, node2);
    printList(result);
    // 释放结果链表的内存
    while (result)
    {
        PolyNode *temp = result;
        result = result->next;
        free(temp);
    }
    return 0;
}
