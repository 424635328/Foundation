//P2249 【深基13.例1】查找

#include <stdio.h>  
int f(int n, int* a, int size) {  
    int l = 0;  
    int r = size - 1;  
    int res = -1;  
    while (l <= r) {  
        int mid = l + (r - l) / 2;  
        if (a[mid] >= n) {  
            r = mid - 1;  
            if (a[mid] == n) res = mid;  
        } else {  
            l = mid + 1;  
        }  
    }  
    return res == -1 ? -1 : (l+1); // 如果未找到，返回-1，否则返回第一次出现的编号（数组索引+1）  
}

int main() {  
    int n, nums;  
    scanf("%d %d", &n, &nums); // 读取数组长度和要查找的数字数量  
  
    int a[n]; // 声明大小为n的数组  
    for (int i = 0; i < n; i++) {  
        scanf("%d", &a[i]); // 读取数组元素  
    }  
  
    int find[nums]; // 声明用于存储要查找数字的数组  
    for (int i = 0; i < nums; i++) {  
        scanf("%d", &find[i]); // 读取要查找的数字  
    }
    for (int i = 0; i < nums; i++) {  
        int index = f(find[i], a, n);  
        printf("%d ", index);  
    }  
  
    return 0;  
}