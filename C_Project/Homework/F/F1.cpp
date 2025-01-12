// 判断给定的二叉树是否为二叉排序树。
#include <bits/stdc++.h>
using namespace std;
typedef struct BiTNode
{
    int data;
    struct BiTNode *lchild;
    struct BiTNode *rchild;
} BiTNode, *BiTree;
int p = 1;
int cmp(int a, int b)
{
    if (a < b)
        return 1;
    return 0;
}

void check(BiTNode *T)
{
    if (T == NULL)
        return;
    if (T->lchild)
    {
        if (!cmp(T->lchild->data, T->data))
        { // 如果左子节点不小于根节点，则不是二叉排序树
            p = 0;
            return;
        }
        check(T->lchild); // 递归检查左子树
    }
    if (T->rchild)
    {
        if (!cmp(T->data, T->rchild->data))
        { // 如果右子节点小于或等于根节点，则不是二叉排序树
            p = 0;
            return;
        }
        check(T->rchild); // 递归检查右子树
    }
}

int main()
{

    //          8
    //         / \
    //       3    10
    //      / \     \    
    //     1   6     14
    // 创建示例二叉排序树
    BiTree T = (BiTNode *)malloc(sizeof(BiTNode));
    T->data = 8;
    T->lchild = (BiTNode *)malloc(sizeof(BiTNode));
    T->lchild->data = 3;
    T->lchild->lchild = (BiTNode *)malloc(sizeof(BiTNode));
    T->lchild->lchild->data = 1;
    T->lchild->lchild->lchild = NULL;
    T->lchild->lchild->rchild = NULL;
    T->lchild->rchild = (BiTNode *)malloc(sizeof(BiTNode));
    T->lchild->rchild->data = 6;
    T->lchild->rchild->lchild = NULL;
    T->lchild->rchild->rchild = NULL;
    T->rchild = (BiTNode *)malloc(sizeof(BiTNode));
    T->rchild->data = 10;
    T->rchild->lchild = NULL;
    T->rchild->rchild = (BiTNode *)malloc(sizeof(BiTNode));
    T->rchild->rchild->data = 14;
    T->rchild->rchild->lchild = NULL;
    T->rchild->rchild->rchild = NULL;
    check(T);
    if (p)
        cout << "Yes";
    else
        cout << "No";
    return 0;
}