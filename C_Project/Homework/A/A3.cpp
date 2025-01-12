// 采用书序表存储图书信息,每本图书包括:序列号,书名,价格.要求:(1)实现图书名称的查找 (2)按图书名的添加(3)按图书名的删除 (4)按定价排序
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 500 // 定义图书的最大容量
typedef struct book
{
    char no[20];
    char name[50];
    float price;
} book;
typedef struct
{
    book *elem;
    int length;
} sqlist;
// 初始化
void initlist(sqlist *l)
{
    int initSize = MAXSIZE;
    l->elem = (book *)malloc(initSize * sizeof(book));
    if (!l->elem)
    {
        exit(1); // 存储分配失败
    }
    l->length = 0; // 空表长度为0
}
// 打印一本书
void printbook(sqlist l, int i)
{
    if (i < 0 || i >= l.length)
    {
        printf("索引无效。\n");
        return;
    }
    printf("序列号: %s\n", l.elem[i].no);
    printf("书名: %s\n", l.elem[i].name);
    printf("价格: %.2f\n", l.elem[i].price);
}
// 打印表中的书
void printall(sqlist l)
{
    printf("表中所有的书有:\n");
    for (int i = 0; i < l.length; i++)
    {
        printf("序列号: %-10s", l.elem[i].no);   // 靠左对齐
        printf("书名: %-20s", l.elem[i].name);   // 靠左对齐
        printf("价格: %.2f\n", l.elem[i].price); // 居中对齐
    }
}
// 定位
int locateelem(sqlist l, char *name)
{
    for (int i = 0; i < l.length; i++) //?i=1
    {
        if (strcmp(l.elem[i].name, name) == 0)
            return i ;
    }
    printf("没有找到。");
    return 0;
}
// 插入,
void listinsert(sqlist &l, char *no, char *name, float price)
{
    int i = 0;
    if (l.length == MAXSIZE)
    {
        printf("添加失败");
        return;
    }
    for (i = 0; i < l.length; i++)
    {
        if (strcmp(l.elem[i].name, name) > 0)
        {
            break;
        }
    }
    for (int j = l.length - 1; j >= i; j--)
    {
        l.elem[j + 1] = l.elem[j];
    }
    strcpy(l.elem[i].no, no);
    strcpy(l.elem[i].name, name);
    l.elem[i].price = price;
    ++l.length;
    printf("添加成功\n");
}
// 删除
void deletebook(sqlist &l, int i)
{
    if (i < 0 || i >= l.length)
    {
        printf("删除失败：索引越界\n");
        return;
    }
    for (int j = i; j < l.length-1; j++)
    {
        strcpy(l.elem[i].name, l.elem[i + 1].name);
        strcpy(l.elem[i].no, l.elem[i + 1].no);
        l.elem[i].price = l.elem[i + 1].price;
    }
    l.length--;
    printf("删除成功\n");
}
// 冒泡排序,小->大
void sortbook(sqlist &l)
{
    int i, j;
    book temp;
    for (i = 0; i < l.length - 1; i++)
    {
        for (j = 0; j < l.length - i - 1; j++)
        {
            if (l.elem[j].price > l.elem[j + 1].price)
            {
                temp = l.elem[j];
                l.elem[j] = l.elem[j + 1];
                l.elem[j + 1] = temp;
            }
        }
    }
}
//销毁
void destroylist(sqlist &l) {
    free(l.elem);
    l.elem=NULL;
    l.length = 0;
}
int main()
{
    int n = 0;
    sqlist l;
    initlist(&l);
    do
    {
        printf("按键:1:按书名查找 2:按书名添加 3:按书名删除 4:按定价排序 -1:退出\n请输入:");
        scanf("%d", &n);
        switch (n)
        {
        case 1:
        {
            printf("输入要查找的书名(拼音&字母):");
            char name1[50];
            scanf("%s", name1);
            printbook(l, locateelem(l, name1));
            break;
        }
        case 2:
        {
            printf("输入要增加的书名(拼音&字母):");
            char name[50];
            scanf("%s", name);
            printf("输入编号:");
            char no[20];
            scanf("%s", no);
            printf("输入价格:");
            float price = 0;
            scanf("%f", &price);
            listinsert(l, no, name, price);
            printall(l);
            break;
        }
        case 3:
        {
            printf("输入要删除的书名(拼音&字母):");
            char name[50];
            scanf("%s", name);
            deletebook(l, locateelem(l, name));
            printall(l);
            break;
        }
        case 4:
        {
            sortbook(l);
            printall(l);
            break;
        }
        case -1:
            printf("退出程序。\n");
            break;
        default:
            printf("无效的选择。\n");
            break;
        }
    } while (n != -1);
    destroylist(l);
    return 0;
}
