// 平衡的括号 Parentheses Balance
#include <iostream>
#include <stack>
#include<algorithm>
using namespace std;
bool judge(stack<char> s)
{
    s.push('#');
    int f = 0;
    string a, b;
    getline(cin, a);//读取一整行
    int n = a.size();
    for (int i = 0; i < n; i++)
    {
        if (a[i] == ' ')
            continue;
        if (a[i] == '(' || a[i] == '[')
        {
            s.push(a[i]);
        }
        else
        {
            if (s.top() == '(' && a[i] == ')')
            {
                s.pop();
                continue;
            }

            if (s.top() == '[' && a[i] == ']')
            {
                s.pop();
                continue;
            }
            return 0;
        }
    }
    
    if (s.size()>1)
        return 0;
    return 1;
}
int main()
{
    
    int n;
    stack<char> s;
    cin >> n;
    getchar(); //hold on
    for (int i = 0; i < n; i++)
    {
        while (!s.empty())
        {
            s.pop();
        }//清空栈
        if (judge(s))
            printf("Yes\n");
        else
            printf("No\n");
    }
}