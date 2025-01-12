// P1464 Function
#include <stdio.h>  
#include <stdlib.h>  
  
#define MAX_N 21  
  
int dp[MAX_N][MAX_N][MAX_N] = {0};  
  
int w(long long a, long long b, long long c) {  
    
    if (a <= 0 || b <= 0 || c <= 0) return 1;  
    if (a > 20 || b > 20 || c > 20) return dp[20][20][20]; 
  
    if (dp[a][b][c] != 0) return dp[a][b][c];  
      
 
    if (a < b && b < c) {  
        dp[a][b][c] = w(a, b, c - 1) + w(a, b - 1, c - 1) - w(a, b - 1, c);  
    } else {  
        dp[a][b][c] = w(a - 1, b, c) + w(a - 1, b - 1, c) + w(a - 1, b, c - 1) - w(a - 1, b - 1, c - 1);  
    }  
      
    return dp[a][b][c];  
}  
  
int main() {   
    w(20, 20, 20); 
    long long a, b, c;  
    while (1) {  
        scanf("%lld %lld %lld", &a, &b, &c);  
        if (a == -1 && b == -1 && c == -1) break;  
        printf("w(%lld, %lld, %lld) = %lld\n", a, b, c, w(a, b, c));  
    }  
      
    return 0;  
}