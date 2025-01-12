// 遍历二叉树，统计节点数据>60的节点个数  
#include<stdio.h>  
#include<stdlib.h>  
  
typedef struct bitnode {  
    int data;  
    struct bitnode *lchild, *rchild;  
} bitnode, *bitree;  
  
// 先序遍历创建二叉树  
void creatbitree(bitree *t, int *arr, int *i) {  
    int n = arr[(*i)++];  
    if (n != 0) {  
        *t = (bitnode *)malloc(sizeof(bitnode));  
        (*t)->data = n;  
        creatbitree(&((*t)->lchild), arr, i);  
        creatbitree(&((*t)->rchild), arr, i);  
    } else {  
        *t = NULL;  
    }  
}  
  
// 遍历二叉树，统计节点数据>60的节点个数  
int nodecount(bitnode *t) {  
    if (!t) return 0;  
    int count = (t->data > 60) ? 1 : 0;  
    count += nodecount(t->lchild);  
    count += nodecount(t->rchild);
    free(t);//释放节点空间  
    return count;  
}  
  
int main() {  
    printf("用0表示空树\n");  
    int arr[] = {1, 3, 66, 0, 61, 0, 0, 0, 0};  
    int i = 0;  
    bitree t;  
  
    creatbitree(&t, arr, &i);  
    int count = nodecount(t);  
    printf("节点数据>60的节点个数: %d\n", count);  
    
    return 0;  
}