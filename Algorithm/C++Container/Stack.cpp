#include <stack>
#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;
int main()
{
    stack<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    q.push(4);
    q.push(5);

    cout << "q.size " << q.size() << endl;
    cout << "q.top " << q.top() << endl; // 输出栈顶元素

    q.pop(); // 删除栈顶元素
    
    cout << "q.size " << q.size() << endl;
    cout << "q.top " << q.top() << endl;

    return 0;
}
/*
stack<int> q;	//以int型为例
int x;
q.push(x);		//将x压入栈顶
push与emplace的异同点
对于int、double等内置数据类型而言，push()和emplace()是相同的
对于自定义数据类型而言，使用push()前必须先将要添加的对象构造出来(实例化)，而使用emplace()既可以填入实例化的对象也可以填入对象的构造参数
q.top();		//返回栈顶的元素
q.pop();		//删除栈顶的元素
q.size();		//返回栈中元素的个数
q.empty();		//检查栈是否为空,若为空返回true,否则返回false
q.swap(q2);     //stackname1.swap(stackname2)
//注意：在堆栈容器中，这些元素以相反的顺序打印，因为先打印顶部，然后再移动到其他元素。
*/