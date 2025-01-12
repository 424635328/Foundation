//P1093 [NOIP2007 普及组] 奖学金

#include<stdio.h>
int max(int *arr,int size,int *a){
    int m=0;
    for(int i=0;i<size;i++){
        if(arr[i]>arr[m]){
            m=i;
        }
        if(arr[i]==arr[m]){
            if(a[i]==a[m])
            m=i<=m?i:m;
            else 
            m=a[i]>a[m]?i:m;
        }
    }
    return m;
}
int main(){
    int n;
    scanf("%d",&n);
    int a[n],b[n],c[n];
    int sum[300]={0};
    for(int i=0;i<n;i++){
        scanf("%d %d %d",&a[i],&b[i],&c[i]);
        sum[i]=a[i]+b[i]+c[i];
    }
    for(int i=0;i<5;i++){
        int r=max(sum,n,a);
        printf("%d %d\n",r+1,sum[r]);
        sum[r]=0;
    }
    return 0;
}