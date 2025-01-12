#include <stdio.h>
#include <stdlib.h>
void swap(int *a, int *b)
{
    int temp = *b;
    *b = *a;
    *a = temp;
}
void max_heapify(int arr[], int start, int end)
{
    // 建立父节点指标和子节点指标
    int dad = start;
    int son = dad * 2 + 1;
    while (son <= end)
    {                                                  // 若子节点指标在范围内才做比较
        if (son + 1 <= end && arr[son] < arr[son + 1]) // 先比较两个子节点大小，选择最大的
            son++;
        if (arr[dad] > arr[son]) // 如果父节点大于子节点代表调整完毕，直接跳出函数
            return;
        else
        { // 否则交换父子内容再继续子节点和孙节点比较
            swap(&arr[dad], &arr[son]);
            dad = son;
            son = dad * 2 + 1;
        }
    }
}
void heap_sort(int arr[], int len)
{
    int i;
    // 初始化，i从最后一个父节点开始调整
    for (i = len / 2 - 1; i >= 0; i--)
        max_heapify(arr, i, len - 1);
    // 先将第一个元素和已排好元素前一位做交换，再从新调整，直到排序完毕
    for (i = len - 1; i >= 0; i--)
    {
        swap(&arr[0], &arr[i]);
        max_heapify(arr, 0, i - 1);
    }
}
int main()
{
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%lld", &arr[i]);
    }
    heap_sort(arr, n);
    for (int i = 0; i < n; i++)
    {
        printf("%lld ", arr[i]);
    }
    return 0;
}