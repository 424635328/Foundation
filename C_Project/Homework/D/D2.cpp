// 设计一个算法，统计输入字符串中各个不同字符出现的频度。（字符串中的合法字符是：26个英文字符和0~9这十个数字）
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define maxlen 100
struct pair
{
    char str;
    int flag;
} pair;
int main()
{
    printf("请输入一段合法字符串:\n");
    char s[maxlen];
    scanf("%s",&s);
    struct pair arr[37] = {{0}};//初始化数组+'\0'
    int n = 0;
    for (int i = 0; i < strlen(s); i++)
    {
        int found = 0;
        for (int j = 0; j < n; j++)// 只需检查已经存储的字符 
        {
            if (arr[j].str == s[i])
            {
                arr[j].flag++;
                found++;
            }
        }
        if (!found)
        {
            arr[n].str = s[i];
            arr[n++].flag++;
        }
    }
    for (int i = 0; i < n; i++)
    {
        printf("%c ,%d\n", arr[i].str, arr[i].flag);
    }
    return 0;
}