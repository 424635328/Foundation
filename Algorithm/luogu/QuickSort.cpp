#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 快速排序函数
void quicksort(vector<int>& arr, int low, int high) {
    if (low < high) {
        // 选择枢轴，这里选择数组最后一个元素作为枢轴
        int pivot = arr[high];
        int i = low - 1;

        // 分区过程，将小于等于枢轴的元素移到左边，大于枢轴的元素移到右边
        for (int j = low; j <= high - 1; j++) {
            if (arr[j] <= pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        // 将枢轴元素放到中间正确的位置
        swap(arr[i + 1], arr[high]);
        quicksort(arr, low, i);
        quicksort(arr, i + 2, high); // 这里应该是 i + 1 而不是 i + 2
    }
}

int main() {
    int n;
    cin >> n; // 读取数组长度
    vector<int> arr(n); // 创建一个长度为n的整数数组
    for (int i = 0; i < n; i++) {
        cin >> arr[i]; // 读取数组元素
    }
    quicksort(arr, 0, n - 1); // 调用快速排序函数对数组进行排序
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " "; // 输出排序后的数组
    }
    return 0;
}