#include <map>
#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;
int main()
{
    map<string, int> m;
    int n;
    cin >> n;
    int op;
    string name;
    int score;
    for (int i = 0; i < n; i++)
    {
        cin >> op;
        if (op == 1)
        {

            cin >> name;
            cin >> score;
            if (m.find(name) != m.end())
                m.erase(name);
            m.insert(pair<string, int>(name, score));
            cout << "OK" << endl;
        }
        if (op == 2)
        {
            cin >> name;
            if (m.find(name) != m.end())
            {
                cout<<m.find(name)->second<<endl;
            }
            else
                cout << "Not found" << endl;
        }
        if (op == 3)
        {
            cin >> name;
            if (m.find(name) != m.end())
            {
                m.erase(name);
                cout << "Deleted successfully" << endl;
            }
            else
                cout << "Not found" << endl;
        }
        if (op == 4)
        {
            cout << m.size() << endl;
        }
    }
    return 0;
}