//P2392 kkksc03考前临时抱佛脚
#include <stdio.h>

int min(int a,int b){
    return a>b?b:a;
}
int max(int a,int b){
    return a>b?a:b;
}
int mintime;
int left =0,right=0;
void gettime(int x,int y,int( *arr)[5],int *a){
    if(x>a[y]){
        mintime=min(mintime,max(left,right));
        return;
    }
    left+=arr[x][y];
    gettime(x+1,y,arr,a);
    left-=arr[x][y];
    right+=arr[x][y];
    gettime(x+1,y,arr,a);
    right-=arr[x][y];
}
int main()
{
	int a[5];
	scanf("%d %d %d %d",&a[1],&a[2],&a[3],&a[4]);
	int arr[21][5];
	for(int i=1;i<=a[1];i++){
		scanf("%d",&arr[i][1]);
	}
	for(int i=1;i<=a[2];i++){
		scanf("%d",&arr[i][2]);
	}
	for(int i=1;i<=a[3];i++){
		scanf("%d",&arr[i][3]);
	}
	for(int i=1;i<=a[4];i++){
		scanf("%d",&arr[i][4]);
	}
    
    int time=0;
    for(int i=1;i<=4;i++){
        left=right=0;
        mintime=2099999999;
        gettime(1,i,arr,a);
        time+=mintime;
    }
	printf("%d",time);
	return 0;
}