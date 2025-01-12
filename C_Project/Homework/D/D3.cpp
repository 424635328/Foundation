// 设计一个稀疏矩阵，采用三元组表存储，并实现转置算法。
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define maxsize 100 // 定义三元组表的最大大小

typedef struct
{
    int i;
    int j;
    int e;
} Triple;

typedef struct
{
    Triple data[maxsize];
    int rows; // 矩阵行数
    int cols; // 列数
    int nums; // 非0元素的个数
} Matrix;

// 初始化
void initmatrix(Matrix &m, int r, int c, int n)
{
    m.rows = r;
    m.cols = c;
    m.nums = n;
    for (int i = 0; i < n; i++)
    {
        m.data[i].i = 0;
        m.data[i].j = 0;
        m.data[i].e = 0;
    }
}

//添加非0元素
void addelem(Matrix &m, int i, int j, int e)
{
    if (m.nums == maxsize)
    {
        printf("矩阵已满!\n");
        return;
    }
    m.data[m.nums].i = i;
    m.data[m.nums].j = j;
    m.data[m.nums].e = e;
    m.nums++;
}

//打印矩阵
void printMatrix(Matrix m)
{
    for (int i = 0; i < m.nums; i++)
    {
        printf("(%d, %d)  %d\n", m.data[i].i, m.data[i].j, m.data[i].e);
    }
}

//转置
void transpose(Matrix m, Matrix &t)
{
    if (t.nums)
    {
        int q = 0;
        for (int col = 1; col <= m.cols; ++col)
            for (int p = 0; p < m.nums; ++p)
                if (m.data[p].j == col)
                {
                    t.data[q].i = m.data[p].j;
                    t.data[q].j = m.data[p].i;
                    t.data[q].e = m.data[p].e;
                    ++q;
                }
    }
}
int main()
{
    srand(time(NULL));
    Matrix M;
    Matrix T;
    initmatrix(M, 6, 7, 0);
    for (int i = 1; i <= M.rows; i++)
    {
        addelem(M, i, rand() % M.cols + 1, rand() % 20 - 9);
    }
    initmatrix(T, M.cols, M.rows, M.nums);
    transpose(M, T);
    printf("转置前:\n");
    printMatrix(M);
    printf("转置后:\n");
    printMatrix(T);
    return 0;
}