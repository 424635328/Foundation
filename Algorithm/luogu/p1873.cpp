//P1873 [COCI 2011/2012 #5] EKO / 砍树
#include <stdio.h>

int N, M;
int trees[1000000];

int check(int height) {
    long long total = 0;
    for (int i = 0; i < N; i++) {
        if (trees[i] > height) {
            total += trees[i] - height;
        }
    }
    return total >= M;
}

int main() {
    scanf("%d %d", &N, &M);
    int max_height = 0;
    for (int i = 0; i < N; i++) {
        scanf("%d", &trees[i]);
        if (trees[i] > max_height) {
            max_height = trees[i];
        }
    }

    int left = 0, right = max_height;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (check(mid)) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    printf("%d\n", right);
    return 0;
}
