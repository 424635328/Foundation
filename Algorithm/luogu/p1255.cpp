//P1255 数楼梯
#include<stdio.h>
#define Max 1044
int n;
int v[5010][5010];

int main(){

    v[1][1] = 1;
	v[2][1] = 2;
    scanf("%d",&n);
    for (int i = 3; i <= n; i++) {
		for (int j = 1; j <= Max; j++) {
           
			v[i][j] += v[i - 1][j] + v[i - 2][j];
			v[i][j + 1] += (v[i][j] / 10);
			v[i][j] %= 10;
		}
	}
	int k = Max;
	while (v[n][k] == 0 && k > 1) {
		k--;
	}

    for (int i = k; i >= 1; i--) {
		printf("%d",v[n][i]);
	}

    return 0;
}
