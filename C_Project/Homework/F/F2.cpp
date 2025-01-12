//设计递归算法，在二叉排序树中，从小到大输出二叉排序树中所有大于等于X结点的数据。
#include <stdio.h>
#include <stdlib.h>
typedef struct BiTNode
{
    int data;
    struct BiTNode *lchild;
    struct BiTNode *rchild;
} BiTNode, *BiTree;
// 在二叉排序树中查找大于等于X的结点并输出
void Find(BiTree T, int x)
{
    if (T == NULL)
    {
        return;
    }
    // 先递归左子树，因为左子树的值小于根节点
    Find(T->lchild, x);
    // 如果当前节点的值大于等于x，则输出
    if (T->data >= x)
    {
        printf("%d ", T->data);
    }
    // 再递归右子树
    Find(T->rchild, x);
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
    int x;
    scanf("%d", &x);
    printf("大于等于 %d 的节点：", x);
    Find(T, x); // 递归
    printf("\n");
    return 0;
}