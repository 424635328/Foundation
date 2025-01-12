#include <array>//下标从0开始
#include <iostream>
#include <algorithm>
using namespace std;
int main(){
    array<int,10> a={1,2,3};
    //cout<<a[10]<<endl;//越界,不报错
    //cout<<a.at(10)<<endl;//越界,报错
    // cout<<a.front()<<" ";
    // cout<<a.back()<<" ";
    //cout<<*(a.data()+2)<<" ";//a[2]的值
    //cout<<a.size()<<" ";//与max_size返回值相同
    //cout<<get<6>(a)<<endl;//即a[6]
    //sort(a.begin(),a.end());
    //reverse(a.begin(),a.end());//a.begin()和a.end()均为一类迭代器
    for(int i:a) cout<<i<<" ";
    return 0;
    //其它基本与vector
}