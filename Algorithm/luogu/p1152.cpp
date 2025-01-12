//P1152 欢乐的跳
#include<stdio.h>
#include<math.h>
void check(long *a,int size,long *flag){
        for(int i=1;i<size;i++){
            if(abs(a[i]-a[i-1])<size&&abs(a[i]-a[i-1])>0){
                flag[abs(a[i]-a[i-1])-1]=abs(a[i]-a[i-1]);
            }
        }
        for(int i=0;i<size-1;i++){
            if(flag[i]==0){
                printf("Not jolly");
                return;
            }
        }
        printf("Jolly");
}
int main(){
    int n;
    scanf("%d",&n);
    long int a[n];
    long int flag[n-1];
    for(int i=0;i<n;i++){
        scanf("%ld",&a[i]);
        if(i<n-1)
        flag[i]=0;
    }
    check(a,n,flag);
    return 0;
}