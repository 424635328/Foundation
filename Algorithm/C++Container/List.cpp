#include <list>
#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;
int main(){
    list<int> l(10);//空间为10，初值为0
    list<int> l1(l);//拷贝列表l
    
    int a[]={1,2,3,4,6,5};
    list<int> l2(a,a+6);
    l2.sort();//list的排序
    l2.reverse();//list的倒序,逆序=排序+倒序
    for(int i:l2) cout<<i<<" ";
    
    auto it=l2.begin();
    return 0;
    //其它基本与vector一致
}