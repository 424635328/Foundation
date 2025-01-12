#include <bits/stdc++.h> 
<<<<<<< HEAD
#include <time.h>        // 包含时间库头文件，用于计时

using namespace std;

#define Maxn 100 // 定义一个常量，表示数组的最大容量

int n;                // 物品的总数
int c;                // 每个箱子的容量
int bestNum;          // 最少的箱子数量
int curNum;           // 当前使用的箱子数量
int curC[Maxn];       // 当前每个箱子的剩余容量
int placed[Maxn];     // 记录每个物品放置的箱子编号
int bestplaced[Maxn]; // 记录最佳方案中每个物品放置的箱子编号

// 回溯算法函数
// 参数：s 是物品大小数组，i 是当前考虑的物品索引
void Backtracking(int *s, int i)
{
    // 剪枝优化：如果当前箱子的剩余容量不足以容纳剩余所有物品，则可以剪枝
    if (curNum > bestNum)
    {
        return;
    }
    // 当所有物品都已考虑时，更新最少箱子数量
    if (i == n)
    {
        if (curNum < bestNum)
        { // 如果当前使用的箱子数量更少，更新最少箱子数量
            bestNum = curNum;
            // 更新最佳方案的物品放置情况
            for (int j = 0; j < n; j++)
            {
                bestplaced[j] = placed[j];
            }
        }
    }
    else
    {
        // 遍历当前使用的箱子
        for (int j = 0; j < curNum; j++)
        {
            // 如果当前箱子剩余容量足够容纳当前物品
            if (curC[j] >= s[i])
            {
                // 将物品放入当前箱子，并递归搜索下一物品
                curC[j] -= s[i];
                placed[i] = j + 1; // 记录物品放置的箱子编号
=======
#include <time.h>       // 包含时间库头文件，用于计时
using namespace std;
#define Maxn 100  // 定义一个常量，表示数组的最大容量
int n;          // 物品的总数
int c;          // 每个箱子的容量
int bestNum;    // 最少的箱子数量
int curNum;     // 当前使用的箱子数量
int curC[Maxn]; // 当前每个箱子的剩余容量

// 回溯算法函数
// 参数：s 是物品大小数组，i 是当前考虑的物品索引
void Backtracking(int *s, int i) {
    // 当所有物品都已考虑时，更新最少箱子数量
    if (i == n) {
        if (curNum < bestNum) {  // 如果当前使用的箱子数量更少，更新最少箱子数量
            bestNum = curNum;
        }
    } else {
        // 遍历当前使用的箱子
        for (int j = 0; j < curNum; j++) {
            // 如果当前箱子剩余容量足够容纳当前物品
            if (curC[j] >= s[i]) {
                // 将物品放入当前箱子，并递归搜索下一物品
                curC[j] -= s[i];
>>>>>>> 7e56557d9608df7db08f6effdc5221cd9bbeda75
                Backtracking(s, i + 1);
                // 恢复当前箱子状态
                curC[j] += s[i];
            }
        }
        // 如果当前使用的箱子数量小于最少箱子数量
<<<<<<< HEAD
        if (curNum < bestNum)
        {
            // 将当前物品放入一个新的箱子，并递归搜索下一物品
            // 初始化新箱子的剩余容量
            curC[curNum] = c - s[i];
            placed[i] = curNum + 1; // 记录物品放置的箱子编号
            // 使用一个新的箱子
            curNum++;
            Backtracking(s, i + 1);
            // 回退使用箱子的数量
            curNum--;
=======
        if (curNum < bestNum) {
            // 将当前物品放入一个新的箱子，并递归搜索下一物品
            curC[curNum] = c - s[i];  // 初始化新箱子的剩余容量
            curNum++;               // 使用一个新的箱子
            Backtracking(s, i + 1);
            curNum--;               // 回退使用箱子的数量
>>>>>>> 7e56557d9608df7db08f6effdc5221cd9bbeda75
        }
    }
}

<<<<<<< HEAD
int main()
{
=======
int main() {
    // 定义物品大小数组
    int s[] ={40, 30, 20, 10, 15, 25, 5, 35, 10, 20, 30, 15, 25, 35, 10, 20, 30, 15, 25, 35};
    // 计算物品数量
    n = sizeof(s) / sizeof(s[0]);
    // 设置箱子容量
    c = 50;
>>>>>>> 7e56557d9608df7db08f6effdc5221cd9bbeda75
    // 定义时间变量
    clock_t start, end;
    double time_used;
    // 记录开始时间
    start = clock();
<<<<<<< HEAD
    // 定义物品大小数组
    int s[] = {47, 48, 49, 1, 14, 49, 46, 6, 45, 37, 47, 22, 22, 3, 2, 16, 44, 20, 3, 34};
    // 计算物品数量
    n = sizeof(s) / sizeof(s[0]);
    // 设置箱子容量c=50
    c = 50;

    // 初始化每个箱子的剩余容量
    for (int i = 0; i < n; i++)
    {
        curC[i] = c;
    }

=======
    // 初始化每个箱子的剩余容量
    for (int i = 0; i < n; i++) {
        curC[i] = c;
    }
>>>>>>> 7e56557d9608df7db08f6effdc5221cd9bbeda75
    // 初始化最少箱子数量
    bestNum = n;
    // 初始化当前使用的箱子数量
    curNum = 0;
<<<<<<< HEAD
    // 排序优化：将物品按照大小从大到小排序
    //sort(s, s + n, greater<int>());
    cout << "物品顺序:" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << s[i] << " ";
    }
    cout << endl;
=======
>>>>>>> 7e56557d9608df7db08f6effdc5221cd9bbeda75
    // 执行回溯算法
    Backtracking(s, 0);
    // 记录结束时间
    end = clock();
    // 计算运行时间
    time_used = (double)(end - start) / CLOCKS_PER_SEC;
<<<<<<< HEAD

    // 输出每个箱子的物品放置情况
    for (int i = 0; i < n; i++)
    {
        cout << "第" << i + 1 << "个物品放在第" << bestplaced[i] << "个箱子" << endl;
    }

    cout << "最少需要" << bestNum << "个箱子" << endl;
    cout << "运行时间为" << time_used << "秒" << endl;
    return 0;
}
=======
    cout<<"最少需要"<<bestNum<<"个箱子"<<endl;
    cout<<"运行时间为"<<time_used<<"秒"<<endl;
    return 0;
}
//能够找到最优解
>>>>>>> 7e56557d9608df7db08f6effdc5221cd9bbeda75
