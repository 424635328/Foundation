// P1303 A*B Problem
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void multi(char *a, char *b, int *c)
{
    int la = strlen(a);
    int lb = strlen(b);
    int lc = la + lb;
    int len = 0;

    for (int i = 0; i <= lc; i++)
    {
        c[i] = 0;
    }

    for (int i = lb - 1; i >= 0; i--)
    {
        for (int j = la - 1; j >= 0; j--)
        {
            int mul = (a[j] - '0') * (b[i] - '0');
            int sum = mul + c[i + j + 1];
            c[i + j + 1] = sum % 10;
            c[i + j] += sum / 10;
        }
    }
    for (len = lc - 1; len >= 0 && c[len] == 0; len--)
    {
        ;
    }
    if (len < 0)
    {
        len = 0;
    }
}
int main()
{
    char a[10500], b[10500];
    int result[21010];
    scanf("%s", a);
    scanf("%s", b);
    int lc = strlen(a) + strlen(b);
    multi(a, b, result);
    int i = 0;
    while (i < lc && result[i] == 0)
    {
        i++;
    }
    if (i == lc)
    {
        printf("0");
    }
    else
    {
        for (; i < lc; i++)
        {
            printf("%d", result[i]);
        }
    }
    return 0;
}