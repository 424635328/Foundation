#include<stdio.h>

int arr[10];
int flag=0;

void initarr(int *arr){
    arr[0]=1;
    for(int i=1;i<10;i++){
        arr[i]=0;
    }
}

int check(int n){
    if(n<123) return 1;
    if(n>987) return 1;
    if(arr[n/100]==1) return 1;
    else arr[n/100]=1;
    n=n%100;
    if(arr[n/10]==1) return 1;
    else arr[n/10]=1;
    n=n%10;
    if(arr[n]==1) return 1;
    else arr[n]=1;
    return 0;
}

void rate(int a,int b,int c){
    for(int i=1;i<=329;i++){ 
        initarr(arr);
        if(check(a*i)) continue;
        else if(check(i*b)) continue;
        else if(check(i*c)) continue;
        else{
            printf("%d %d %d\n",a*i,i*b,i*c);
            flag++;
        }
    }
    if(!flag) printf("No!!!");
}

int main(){
    int a,b,c;
    scanf("%d %d %d",&a,&b,&c);
    rate(a,b,c);
    return 0;
}