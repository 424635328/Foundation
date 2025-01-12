//输出二叉树中结点数据>60的结点所在的层次，并输出该节点。
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
  
// 遍历二叉树，找出节点数据>60的节点
void find(bitnode *t,int *n){
    if(t==NULL) return;
    (*n)++;
    if(t->data>60){
        printf("层次:%d 节点:%d\n",*n,t->data);
    }
    find(t->lchild,n);
    find(t->rchild,n);
}
  
int main() {  
    printf("用0表示空树\n");  
    int arr[] = {1, 3, 66, 0, 61, 0, 0, 0, 0};  
    int i = 0;  
    bitree t;  
  
    creatbitree(&t, arr, &i);  
    int n=0;
    find(t,&n);
    return 0;  
}