// 假设以字符串的形式存储二叉树的,  根, 左子树, 右子树.请根据字符序列:
// A(B(   ,C(   ,   )),D(   ,   )),创建对应的二叉树,并输出先序遍历和中序遍历。
#include <stdio.h>
#include <stdlib.h>

typedef struct bitnode
{
    char data;
    struct bitnode *lchild, *rchild;
} bitnode, *bitree;

// 先序遍历创建二叉树
void creatbitree(bitree *t, char *arr, int *i)
{
    char n = arr[(*i)++];
    if (n != '#')
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
// 输出先序遍历
void outputs(bitnode *t)
{
    if (t == NULL)
        return;
    else
    {
        printf("%c ", t->data);
        outputs(t->lchild);
        outputs(t->rchild);
    }
}
// 输出中序遍历
void outputm(bitnode *t)
{
    if (t == NULL)
        return;
    else
    {
        outputm(t->lchild);
        printf("%c ", t->data);
        outputm(t->rchild);
    }
}
int main()
{
    printf("用0表示空树\n");
    char arr[] = {'A', 'B', '#', 'C', '#', '#', 'D', '#', '#'};
    int i = 0;
    bitree t;
    creatbitree(&t, arr, &i);
    int n = 0;
    printf("先序遍历为:\n");
    outputs(t);
    printf("\n");
    printf("中序遍历为:\n");
    outputm(t);
    return 0;
}