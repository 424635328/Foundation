//判断一颗树是否为平衡二叉树。
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct BiTNode {
    int data;
    struct BiTNode *lchild;
    struct BiTNode *rchild;
} BiTNode, *BiTree;

// 获取树的高度
int getHeight(BiTree T) {
    if (T == NULL) {
        return 0;
    }
    int leftHeight = getHeight(T->lchild);
    int rightHeight = getHeight(T->rchild);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

// 判断是否为平衡二叉树
bool isBalanced(BiTree T) {
    if (T == NULL) {
        return true;
    }

    int leftHeight = getHeight(T->lchild);
    int rightHeight = getHeight(T->rchild);

    // 左右子树高度差的绝对值超过 1，则不是平衡二叉树
    if (abs(leftHeight - rightHeight) > 1) {
        return false;
    }

    // 递归检查左右子树是否为平衡二叉树
    return isBalanced(T->lchild) && isBalanced(T->rchild);
}

int main() {
    // 创建示例二叉排序树
    //          8
    //         / \
    //       3    10
    //      / \     \    
    //     1   6     14
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

    if (isBalanced(T)) {
        printf("该树是平衡二叉树\n");
    } else {
        printf("该树不是平衡二叉树\n");
    }

    return 0;
}