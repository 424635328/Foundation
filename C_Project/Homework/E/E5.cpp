// 计算树的深度。
#include <stdio.h>
#include <stdlib.h>

typedef struct bitnode
{
    int data;
    struct bitnode *lchild, *rchild;
} bitnode, *bitree;

// 先序遍历创建二叉树
void creatbitree(bitree *t, int *arr, int *i)
{
    int n = arr[(*i)++];
    if (n != 0)
    {
        *t = (bitnode *)malloc(sizeof(bitnode));
        (*t)->data = n;
        creatbitree(&((*t)->lchild), arr, i);
        creatbitree(&((*t)->rchild), arr, i);
    }
    else
    {
        *t = NULL;
    }
}

// 遍历二叉树
int depth(bitnode *t)
{
    if(t==NULL) return 0;
    else{
        int m=depth(t->lchild);
        int n=depth(t->rchild);
        return m>n?m+1:n+1;
    }
}

int main()
{
    printf("用0表示空树\n");
    int arr[] = {1, 3, 66, 1, 0, 0, 61, 0, 0, 0, 0};//4层
    int i = 0;
    bitree t;
    creatbitree(&t, arr, &i);
    int n = 0;
    printf("%d", depth(t));
    return 0;
}