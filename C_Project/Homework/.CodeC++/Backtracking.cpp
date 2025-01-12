#include <stdio.h>
#include <stdlib.h>
#define Maxn 100
int n;          // 物品的总数
int c;          // 每个箱子的容量
int bestNum;    // 最少的箱子数量
int curNum;     // 当前使用的箱子数量
int curC[Maxn]; // 当前每个箱子的剩余容量

void Backtracking(int *s, int i) {
    if (i == n) {
        if (curNum < bestNum) {
            bestNum = curNum;
        }
    } else {
        for (int j = 0; j < curNum; j++) {
            if (curC[j] >= s[i]) {
                curC[j] -= s[i];
                Backtracking(s, i + 1);
                curC[j] += s[i];
            }
        }
        if (curNum < bestNum) {
            curC[curNum] = c - s[i];
            curNum++;
            Backtracking(s, i + 1);
            curNum--;
        }
    }
}

int main() {
    int s[] = {20, 6, 57, 67, 45, 69, 18, 16, 33, 21, 1, 62, 51, 56, 57, 67, 51, 49, 70, 50};    // 物品大小
    n = sizeof(s) / sizeof(s[0]); // 物品数量
    c = 100;                        // 箱子容量
    for (int i = 0; i < n; i++) { // 初始化 curC
        curC[i] = c;
    }
    bestNum = n;                  // 初始化 bestNum
    curNum = 0;                   // 初始化 curNum
    Backtracking(s, 0);
    printf("最少需要%d 个箱子", bestNum);
    return 0;
}
