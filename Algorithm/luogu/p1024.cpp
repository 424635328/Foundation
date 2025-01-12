//P1024 [NOIP2001 提高组] 一元三次方程求解

#include <stdio.h>
#include <math.h>

double a, b, c, d;

double f(double x)
{
    return a * x * x * x + b * x * x + c * x + d;
}

void findRoot(double left, double right)
{

    if ((right - left < 0.01))
    {
        printf("%.2lf ", (left + right) / 2);
        return;
    }
    double mid = left + (right - left) / 2;
    if (f(left) * f(mid) < 0)
    {
        findRoot(left, mid);
    }
    else
    {
        findRoot(mid, right);
    }
}

int main()
{
    scanf("%lf %lf %lf %lf", &a, &b, &c, &d);
    int flag=0;
    if(f(-100)==0){
         printf("%.2lf ", -100);
        flag++;
    }
    if(f(100)==0){
         printf("%.2lf ", 100);
        flag++;
    }
    int l=-100;
    int r=100;
    while(l<=r){
        int mid=(l+r)/2;
        
    }


    return 0;
}
