//采用先序遍历思想建立二叉树,树中结点数据为整数。
 #include<stdio.h>
 typedef struct bitnode
 {
    int data;
    struct bitnode *lchild,*rchild;
 }bitnode,*bitree;
 int n;
 void creatbitree(bitree &t){
    scanf("%d",&n);
    if(n!=0){
        t=new bitnode;
        t->data=n;
        creatbitree(t->lchild);
        creatbitree(t->rchild);
    }
    else return ;
 }
 int main(){
    printf("用0表示空树\n");
    bitree t;
    creatbitree(t);
    return 0;
 }