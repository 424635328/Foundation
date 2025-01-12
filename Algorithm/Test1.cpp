#include <stdio.h>
#include <bits/stdc++.h>
using namespace std;

int N;

void shellSort(int *arr, int size) {
  // 确定步长序列，可以使用 Knuth 的 3x+1 步长序列
  for (int d = size / 2; d > 0; d /= 2) {
    // 对每个步长进行插入排序
    for (int i = d; i < size; i++) {
      int key = arr[i];
      int j = i;
      // 将元素插入到它应该在的正确位置
      while (j >= d && arr[j - d] > key) {
        arr[j] = arr[j - d];
        j -= d;
      }
      arr[j] = key;
    }
  }
}

int main() {
  cin >> N;
  int arr[N];
  for (int i = 0; i < N; i++) {
    cin >> arr[i];
  }
  shellSort(arr, N);
  for (int i = 0; i < N; i++) {
    cout << arr[i] << " ";
  }
  return 0;
}