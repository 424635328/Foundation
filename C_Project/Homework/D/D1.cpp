// 4.6 4.7 KMP ababcabcacbab abcac
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// 计算next函数的修正值
void getnext(char *T, int next[])
{
    int i = 1, j = 0;
    next[1] = 0;
    while (i < strlen(T))
    {
        if (j == 0 || T[i] == T[j])
        {
            i++;
            j++;
            if (T[i] != T[j])
                next[i] = j;
            else
                next[i] = next[j];
        }
        else
            j = next[j];
    }
}
// 进行匹配
int KMP(char *S, char *T, int next[])
{
    int lenS = strlen(S);
    int lenT = strlen(T);
    
    int i = 0, j = 0;
    while (i < lenS && j < lenT)
    {
        if (j == -1 || S[i] == T[j])
        {
            i++;
            j++;
        }
        else
        {
            j = next[j];
        }
    }
    if (j == lenT)
    {
        return i - j; // 返回模式串在的起始位置
    }
    else
    {
        return 0;
    }
}
int main()
{
    char S[] = "ababcabcacbab";
    char T[] = "abcac";
    int *next = (int *)malloc(sizeof(int) * strlen(T));
    getnext(T, next);
    int p = KMP(S, T, next);
    if (p != -1)
        printf("模式串在主串的位置为:%d", p);
    else
        printf("没有找到");
    return 0;
}