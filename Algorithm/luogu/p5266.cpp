#include <iostream>
#include <cstring>
#include <map>
using namespace std;
map<string, int> a; // a[string]=int
int main()
{
    int m, n;
    scanf("%d", &m);
    string name;
    for (int i = 0; i < m; i++)
    {
        scanf("%d", &n);
        if (n != 4)
            cin >> name;
        switch (n)
        {
        case 1:
            int score;
            scanf("%d", &score);
            a[name] = score;
            printf("OK\n");
            break;
        case 2:
            if (a.count(name))
                printf("%d\n", a[name]);
            else
                printf("Not found\n");
            break;
        case 3:
            if (a.count(name))
            {
                a.erase(name);
                printf("Deleted successfully\n");
            }
            else
                printf("Not found\n");
            break;
        case 4:
            printf("%d\n", a.size());
            break;
        }
    }
    return 0;
}