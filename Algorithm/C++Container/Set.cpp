#include <set>
#include <iostream>
#include <algorithm>
using namespace std;
int main(){
    set<int> s={1,2,3,6};
    int a[]={1,2,3,4,6,5,6};
    set<int> s1(begin(a),end(a));
    s.insert(7);
    s.insert(5);
    //sort(s.begin(),s.end());//多余，set是有序的
    //reverse(s.begin(),s.end());//报错,
    //s1.clear();//清空
    //s.erase(6);
    //auto it=s1.find(1);//find()，返回给定值值得定位器，如果没找到则返回end()。
    //cout<<*it<<" ";
    //auto it =s.lower_bound(2);//返回第一个大于等于key_value的定位器
    //s.upper_bound(val)//返回最后一个大于等于key_value的定位器
    
    cout<<s1.count(6)<<endl;
    for(auto i:s1) cout<<i<<" ";
    return 0;
}