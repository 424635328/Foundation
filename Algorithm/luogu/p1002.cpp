//P1002 [NOIP2002 普及组] 过河卒
#include <stdio.h>
#include <math.h>
long long dp[21][21];
void ToD(float bx, float by, float hx, float hy, long long dp[21][21])
{
    
    dp[0][0]=1;
    for (int i = 0; i <= bx; i++)
    {
        for (int j = 0; j <= by; j++)
        {
            if (i == 0 && j == 0) continue;  
            if (((hy - j) * (hy - j)) + ((hx - i) * (hx - i)) == 5||(i==hx&&j==hy))
            {
                dp[i][j] = 0;
            }
            else
             dp[i][j] = (i > 0 ? dp[i - 1][j] : 0) + (j > 0 ? dp[i][j - 1] : 0); 
        }
    }
    printf("%lld\n", dp[(int)bx][(int)by]);
}
int main()
{
    
    float bx, by, hx, hy;
    scanf("%f %f %f %f", &bx, &by, &hx, &hy);
    ToD(bx, by, hx, hy, dp);
    return 0;
}