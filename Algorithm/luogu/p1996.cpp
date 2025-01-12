//P1996 约瑟夫问题
#include<stdio.h>
#include<stdlib.h>
typedef struct listnode
{
    int data;
    struct listnode*next;
}listnode;

int main(){
    struct listnode*head=NULL;
    struct listnode*dummy=NULL;
    int m,n;
    scanf("%d %d",&m,&n);
    for(int i=0;i<m;i++){
         listnode*newnode=(listnode*)malloc(sizeof(listnode));
        newnode->data=i+1;
        newnode->next=NULL;
        if(head==NULL) {
            head=newnode;
            dummy=newnode;
        }
        dummy->next=newnode;
        dummy=dummy->next;
    }
    dummy->next=head;
    int t=1;
    int s=n-1;
    while(head->next!=head){
        t++;
        head=head->next;
        if(!(t%s)) {
            printf("%d ",head->next->data);
            head->next=head->next->next;
        }
    }
    printf("%d",head->data);
    return 0;

}