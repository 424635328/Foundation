//P1803 凌乱的yyy / 线段覆盖
#include <iostream>
#include <algorithm>

using namespace std;

struct niop {
    int start;
    int end;
};

// 比较函数，根据结束时间升序排序
bool compare( niop a, niop b) {
    return a.end<b.end;
}

int main() {
    int N;
    cin >> N;
    niop com[N];
    for (int i = 0; i < N; i++) {
        cin >> com[i].start >> com[i].end;
    }

    // 使用 std::sort 排序 com 数组
    sort(com, com + N, compare);

    // 选择最优的安排方案
    int st = 0;
    int n = 0;
    for (int i = 0; i < N; i++) {
        if (com[i].start >= st) {
            st = com[i].end;
            n++;
        }
    }
    cout << n;
    return 0;
}