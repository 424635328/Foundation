// 编程实现两个升序有序表的升序归并算法
#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 25 // 设置最大表长
// 定义一个顺序表的结构体
typedef struct sqlist
{
    int *elem;
    int length;
} sqlist;
// 初始化
void initsqlist(sqlist &l)
{
    l.elem = (int *)malloc(MAXSIZE * sizeof(int));
    if (!l.elem)
    {
        exit(1);
    }
    l.length = 0;
}
// 归并
void merge(sqlist &l1, sqlist &l2, sqlist &l)
{
    int i, j;
    l.length = l1.length + l2.length;
    for (i = 0; i <= l.length; i++)
    {
        if (i < l1.length)
        {
            l.elem[i] = l1.elem[i];
        }
        else
        {
            l.elem[i] = l2.elem[i - l1.length];
        }
    }
    int temp = 0;
    for (i = 0; i < l.length; i++)
    {
        for (j = 0; j < l.length - i - 1; j++)
        {
            if (l.elem[j] > l.elem[j + 1])
            {
                temp = l.elem[j + 1];
                l.elem[j + 1] = l.elem[j];
                l.elem[j] = temp;
            }
        }
    }
}
// 打印
void printlist(sqlist l)
{
    for (int i = 0; i < l.length; i++)
    {
        printf("%d ", l.elem[i]);
    }
}
int main()
{
    sqlist l1;
    sqlist l2;
    sqlist l;
    initsqlist(l1);
    initsqlist(l2);
    initsqlist(l);
    int n = 0, i = 0, j = 0;
    printf("请输入l1中的元素(输入-1退出):");
    scanf("%d", &n);
    while (n != (-1))
    {

        l1.elem[i++] = n;
        l1.length++;
        scanf("%d", &n);
    }
    printf("请输入l2中的元素(输入-1退出):");
    scanf("%d", &n);
    while (n != (-1))
    {

        l2.elem[j++] = n;
        l2.length++;
        scanf("%d", &n);
    }

    merge(l1, l2, l);
    printlist(l);
    return 0;
}