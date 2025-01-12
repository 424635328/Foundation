//统计二叉树中度为2的结点个数。

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
  
// 遍历二叉树
void count(bitnode *t,int *n){
    if(t==NULL) return;
    if(t->lchild!=NULL&&t->rchild!=NULL) (*n)++;
    count(t->lchild,n);
    count(t->rchild,n);
    
}
  
int main() {  
    printf("用0表示空树\n");  
    int arr[] = {1, 3, 66, 1,0,0, 61, 0, 0, 0, 0};  
    int i = 0;  
    bitree t;  
  
    creatbitree(&t, arr, &i);  
    int n=0;
    count(t,&n);
    printf("%d",n);
    return 0;  
}