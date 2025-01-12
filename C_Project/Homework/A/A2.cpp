// 采用顺序表存储稀疏多项式非零项的系数及其指数,并实现两个稀疏多项式的加法运算.
#include <stdio.h>
#include <stdlib.h>
#define END -1 // 定义多项式的结束标志

typedef struct poly
{
    int coe;   // 系数
    float exp; // 指数
} poly;

typedef struct SeqList
{
    poly *data; // 数据元素的指针
    int length; // 表长
} SeqList;

// 初始化并将表长设为 0
SeqList *InitSeqList(int size)
{
    SeqList *L = (SeqList *)malloc(sizeof(SeqList));
    L->data = (poly *)malloc(size * sizeof(poly));
    L->length = 0;
    return L;
}

void InsertSeqList(SeqList *L, poly e)
{
    L->data[L->length] = e;
    L->length++;
}

// 多项式相加
poly *add(poly *p1, int m, poly *p2, int n)
{
    poly *result = (poly *)malloc((m + n + 1) * sizeof(poly));
    int i = 0, j = 0, k = 0;

    // 遍历两个多项式
    while (i < m && j < n)
    {
        if (p1[i].exp < p2[j].exp)
        {
            result[k] = p1[i];
            i++;
        }
        else if (p1[i].exp > p2[j].exp)
        {
            result[k] = p2[j];
            j++;
        }
        else
        {
            result[k].exp = p1[i].exp;
            result[k].coe = p1[i].coe + p2[j].coe;
            i++;
            j++;
        }
        k++;
    }

    // 如果还有余项
    while (i < m)
    {
        result[k] = p1[i];
        i++;
        k++;
    }
    while (j < n)
    {
        result[k] = p2[j];
        j++;
        k++;
    }

    // 添加结束标志
    result[k].coe = END;
    result[k].exp = END;

    return result;
}

void printpoly(poly *p)
{
    int i = 0;
    while (p[i].coe != END)
    {
        printf("%d*x^%.1f ", p[i].coe, p[i].exp);
        if (p[i + 1].coe != END)
        {
            printf("+ ");
        }
        i++;
    }
    printf("\n");
}

int main()
{
    SeqList *p1 = InitSeqList(5);
    InsertSeqList(p1, (poly){1, 0});
    InsertSeqList(p1, (poly){2, 1});
    InsertSeqList(p1, (poly){3, 3});
    InsertSeqList(p1, (poly){5, 6});
    InsertSeqList(p1, (poly){END, END});

    SeqList *p2 = InitSeqList(4);
    InsertSeqList(p2, (poly){3, 0});
    InsertSeqList(p2, (poly){4, 2});
    InsertSeqList(p2, (poly){2, 3});
    InsertSeqList(p2, (poly){END, END});

    poly *p = add(p1->data, p1->length, p2->data, p2->length);
    printpoly(p);
    return 0;
}
