#include <stdio.h>
#include <stdlib.h>
void firstFitDecreasing(int s[], int n, int c) {
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
    // 遍历物品并尝试放入箱子
    for (i = 0; i < n; i++) {
        int placed = 0; // 标记物品是否已放入箱子
        for (j = 0; j < binsUsed; j++) {
            if (bins[j] + s[i] <= c) { // 如果当前箱子可以放下物品
                bins[j] += s[i]; // 放入物品
                printf("第%d个物品放在第%d个箱子\n",i+1,j+1);
                placed = 1;
                break;
            }
        }
        if (!placed) { // 如果所有箱子都放不下物品，则开新箱子
            bins[binsUsed] = s[i];
            printf("第%d个物品放在第%d个箱子\n",i+1,binsUsed+++1);
        }
    }

    // 输出结果
    printf("需要 %d 个箱子\n", binsUsed);
    free(bins);
}

int main() {
    int s[] = {3, 2, 5, 1, 4,8 ,9}; // 物品大小
    int n = sizeof(s) / sizeof(s[0]); // 物品数量
    int c = 6; // 箱子容量
    firstFitDecreasing(s, n, c);
    return 0;
}