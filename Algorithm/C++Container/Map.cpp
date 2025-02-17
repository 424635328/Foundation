#include <map>
#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;
int main()
{
    map<int, string> m;
    m.insert(pair<int, string>(1, "stu1"));
    m.insert(pair<int, string>(3, "stu3"));
    m.insert(pair<int, string>(2, "stu2"));
    auto t=m.begin();
    size_t position = distance(t, m.end()); // 迭代器与map末尾的距离 这里为1
    while(t!=m.end()){
        cout<<t->first<<" "<<t->second<<endl;
        t++;
    }
    return 0;
}
/*C++ Maps是一种关联式容器，包含“关键字/值”对
begin() 返回指向map头部的迭代器
clear(） 删除所有元素
count() 返回指定元素出现的次数
empty() 如果map为空则返回true
end() 返回指向map末尾的迭代器,指向最后一个元素末尾
equal_range() 返回特殊条目的迭代器对
erase() 删除一个元素
find() 查找一个元素
get_allocator() 返回map的配置器
insert() 插入元素
key_comp() 返回比较元素key的函数
lower_bound() 返回键值>=给定元素的第一个位置
max_size() 返回可以容纳的最大元素个数
rbegin() 返回一个指向map尾部的逆向迭代器
rend() 返回一个指向map头部的逆向迭代器
size() 返回map中元素的个数
swap() 交换两个map
upper_bound() 返回键值>给定元素的第一个位置
value_comp() 返回比较元素value的函数*/