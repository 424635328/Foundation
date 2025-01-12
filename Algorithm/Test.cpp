<<<<<<< HEAD
#include <iostream>

using namespace std;

int main() {
  int tenCount, fiveCount, oneCount, fiftyCount;
  int totalCombinations = 0;

  // 遍历所有可能的10元纸币数量
  for (tenCount = 0; tenCount <= 10; ++tenCount) {
    // 遍历所有可能的5元纸币数量
    for (fiveCount = 0; fiveCount <= 20; ++fiveCount) {
      // 遍历所有可能的1元纸币数量
      for (oneCount = 0; oneCount <= 100; ++oneCount) {
        // 遍历所有可能的5毛纸币数量
        for (fiftyCount = 0; fiftyCount <= 200; ++fiftyCount) {
          // 检查是否满足总金额为100元
          if (10 * tenCount + 5 * fiveCount + oneCount + 0.5 * fiftyCount == 100) {
            ++totalCombinations;
            // 可以选择打印每种换法
            // cout << "10元: " << tenCount << ", 5元: " << fiveCount << ", 1元: " << oneCount << ", 5毛: " << fiftyCount << endl;
          }
        }
      }
    }
  }

  cout << "总共有 " << totalCombinations << " 种换法" << endl;

=======
#include <bits/stdc++.h>

using namespace std;

int m=1;
void fun(){
  m=3;
}
int main() {
  cout<<m<<endl;
  m=2;
  cout<<m<<endl;
  fun();
  cout<<m<<endl;
>>>>>>> 7e56557d9608df7db08f6effdc5221cd9bbeda75
  return 0;
}