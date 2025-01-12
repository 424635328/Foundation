#include <stdio.h>
#include <stdlib.h>
void loading(int *s,int n,int c){
    int *bins = (int *)calloc(n, sizeof(int)); // 初始化箱子状态
    int binsUsed = 0; // 记录使用的箱子数
    int i, j;

    // 先对物品按大小降序排序
    
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (s[i] < s[j]) {
                int temp = s[i];
                s[i] = s[j];
                s[j] = temp;

            }

        }
    }
    printf("排序后的物品顺序:");
    for(i=0;i<n;i++){
        printf("%d ",s[i]);
    }
    printf("\n");

    


}
int main() {
    int s[] = {3, 2, 5, 1, 4,8 ,9}; // 物品大小
    int n = sizeof(s) / sizeof(s[0]); // 物品数量
    int c = 6; // 箱子容量
    loading(s, n, c);
    return 0;
}