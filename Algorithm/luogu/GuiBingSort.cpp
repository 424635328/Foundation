#include <stdio.h>
#include <stdlib.h>
// 归并时间少，快排内存小

void merge(int arr[], int left[], int lsize, int right[], int rsize, int start)
{
    int i = 0, j = 0, k = start;
    while (i < lsize && j < rsize)
    {
        if (left[i] <= right[j])
        {
            arr[k] = left[i];
            i++;
        }
        else
        {
            arr[k] = right[j];
            j++;
        }
        k++;
    }
    while (i < lsize)
    {
        arr[k] = left[i];
        i++;
        k++;
    }
    while (j < rsize)
    {
        arr[k] = right[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int size)
{
    if (size < 2)
    {
        return;
    }
    int mid = size / 2;
    int *left = (int *)malloc(mid * sizeof(int));
    int *right = (int *)malloc((size - mid) * sizeof(int));

    for (int i = 0; i < mid; i++)
    {
        left[i] = arr[i];
    }
    for (int j = mid; j < size; j++)
    {
        right[j - mid] = arr[j];
    }

    mergeSort(left, mid);
    mergeSort(right, size - mid);

    merge(arr, left, mid, right, size - mid, 0);

    free(left);
    free(right);
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
    mergeSort(arr,n);
    for (int i = 0; i < n; i++)
    {
        printf("%lld ", arr[i]);
    }
    return 0;
}