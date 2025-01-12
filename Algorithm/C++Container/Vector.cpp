#include <vector>
#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;
int main()
{
    int a[]={1,2,3,4,6,5};
    vector<int> v3(a,a+6);
    vector<int> v(10, 5);                      // 容器大小为10,元素初始化为5
    vector<int> v1{1,1,0,0,0, 5, 6, 9,9, 9, 1, 2, 4, 6,0,0,0,}; // 使用列表初始化创建vector
    // v1.push_back(0);                           // 向容器末尾添加元素
    //  cout << v1.back() << " ";            // 输出末尾元素
    //  cout << v1.front() << " ";           // 输出第一个元素
    // v1.pop_back(); // 删除末尾元素
   // v1.push_back(100);
    
    sort(v1.begin(), v1.end()); // 排序
    // reverse(v1.begin(), v1.end()); // 逆序,倒序=排序+逆序
    // v1.resize(12); // 新元素初值为0
    // for(int i:v1) printf("%d ",i);    //可以遍历v1将所有依次赋值给i
    // v1=v;                             //用v替换v1
    for (int i = 0; i < v3.size(); i++)
    {
        cout << v3[i] << " "; // 用下标输出元素
    }
    cout << endl;
    vector<int>::iterator it = v1.begin(); // 迭代器iterator
                          // v1.insert(it, {1, 2, 3}); // 在第一个元素前插入{1，2，3}三个元素,it位置会改变
    // it = v1.begin();

    // v1.erase(it+10);//删除第十一个元素,it位置不改变
    //auto=vector<int>::iterator
    auto end_unique = unique(v1.begin(), v1.end()); // 将相邻重复元素消除,迭代器移动到第一个不重复元素的末尾
     v1.erase(end_unique, v1.end());                 // 删除末尾的重复元素
    while (it != v1.end())
    {
        cout << *it << " ";
        it++;
    }
    cout << endl;
    it = max_element(v1.begin(), v1.end()); // 找最值(min_element)
    cout << *it << " ";

    return 0;
}