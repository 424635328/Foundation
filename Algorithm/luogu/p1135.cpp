#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <queue>
using namespace std;
int N, A, B;
vector<int> v(201);
queue<int> q, qs;
int d[2] = {1, -1};
int vis[201], m[201];
int check(int a)
{
    if (a < 0 || a >= N)
        return 0;
    return 1;
}
void arrive()
{
    int a;
    int s;
    while (!q.empty())
    {

        a = q.front();
        s = qs.front();
        q.pop();
        qs.pop();
        m[a] = s;
        for (int i = 0; i < 2; i++)
        {
            for (int j = 1; j <= v[a]; j++)
            {
                if (check(a + d[i] * j) && !vis[a + d[i] * j])
                {
                    vis[a + d[i] * j] = 1;
                    q.push(a + d[i] * j);
                    if (j == v[a])
                        qs.push(s + 1);
                    else
                        qs.push(s + 2);
                }
            }
        }
    }
}
int main()
{
    cin >> N, cin >> A, cin >> B;
    for (int i = 0; i < N; i++)
    {
        cin >> v[i];
    }
    q.push(A - 1);
    qs.push(0);
    arrive();
    cout << m[B - 1];
    return 0;
}