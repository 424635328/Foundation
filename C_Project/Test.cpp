#include <stdio.h>
int  f(int n, int* a,int size) {
    int x = -1;
    int l = 0;
    int r = size-1;
    int mid = (l + r) / 2;
    while(l<=r){
        if (n < a[mid]) {
            r = mid;
            mid = (l + r) / 2;
        }
        if (n > a[mid]) {
            l = mid;
            mid = (l + r) / 2;
        }
        if (n == a[mid]) {
            x = mid;
            return x+1;
        }
    }
    return x;
}
int main() {
    int n =0;
    scanf("%d", &n);
    int nums = 0;
    scanf("%d", &nums);
    int a[10000] = { 0 };
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    int find[nums]={0};
    for(int i=0;i<nums;i++)
    {
       
        scanf("%d", &find[i]);
        
    }
    for(int i=0;i<nums;i++){
        printf("%d", f(find[i], a,n));
    }
    return 0;
}