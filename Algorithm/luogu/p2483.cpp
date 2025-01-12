//P2483 【模板】k 短路 / [SDOI2010] 魔法猪学院
#include <bits/stdc++.h>
using namespace std;
#define pii pair<double, int>
const double ep = 1e-8;
const int N = 10005;
const int M = 200005;
int n, m;
double E;
int f[N];
int st[N];
bool vis[N];
int top;
bool line[M];
double energy[N];
int root[N];

struct node
{
    int id, v;
    double w;
};
vector<node> road[N], rroad[N];

namespace LT
{
    struct point
    {
        int lson, rson, last;
        int energy;
        double val;
    } tr[M * 20];
    int cnt = 0;
    int create(double v, int last)
    {
        int u = ++cnt;
        tr[u].val = v;
        tr[u].last = last;
        tr[u].energy = tr[u].lson = tr[u].rson = 0;
        return cnt;
    }
    int cop(int id)
    {
        int u = ++cnt;
        tr[u] = tr[id];
        return u;
    }
    int merge(int x, int y)
    {
        if (x == 0 || y == 0)
        {
            return x | y;
        }
        if (tr[x].val > tr[y].val)
        {
            swap(x, y);
        }
        int u = cop(x);
        tr[u].rson = merge(tr[u].rson, y);
        if (tr[tr[u].lson].energy < tr[tr[u].rson].energy)
        {
            swap(tr[u].lson, tr[u].rson);
        }
        tr[u].energy = tr[tr[u].rson].energy + 1;
        return u;
    }
    void insert(int &rt, double val, int last)
    {
        rt = merge(create(val, last), rt);
    }
}

using namespace LT;
priority_queue<pii, vector<pii>, greater<pii>> q;

void dij()
{
    for (int i = 0; i < N; i++)
    {
        energy[i] = 1e9;
    }
    energy[n] = 0;
    q.push((pii){0.0, n});
    while (!q.empty())
    {
        int u = q.top().second;
        double len = q.top().first;
        q.pop();
        if (energy[u] != len)
        {
            continue;
        }
        for (int i = 0; i < rroad[u].size(); i++)
        {
            int v = rroad[u][i].v;
            double l = rroad[u][i].w;
            if (energy[v] > energy[u] + l)
            {
                energy[v] = energy[u] + l;
                q.push((pii){energy[v], v});
            }
        }
    }
}

void dfs(int u)
{
    st[++top] = u;
    vis[u] = true;
    for (int i = 0; i < rroad[u].size(); i++)
    {
        int v = rroad[u][i].v;
        double l = rroad[u][i].w;
        if (energy[v] == energy[u] + l && vis[v] == false)
        {
            line[rroad[u][i].id] = true;
            f[v] = u;
            dfs(v);
        }
    }
}

void build()
{
    for (int i = 1; i <= top; i++)
    {
        int u = st[i];
        root[u] = root[f[u]];
        for (int i = 0; i < road[u].size(); i++)
        {
            int id = road[u][i].id;
            int v = road[u][i].v;
            double w = road[u][i].w;
            if (!line[id] && energy[v] != energy[0])
            {
                insert(root[u], energy[v] + w - energy[u], v);
            }
        }
    }
}

int kshort()
{
    int cnt = 1;
    E -= energy[1];
    priority_queue<pii, vector<pii>, greater<pii>> q;
    q.push((pii){energy[1] + tr[root[1]].val, root[1]});
    while (!q.empty())
    {
        double len = q.top().first;
        int u = q.top().second;
        q.pop();
        if (len - ep > E)
            break;
        E -= len - ep;
        cnt++;
        int l = tr[u].lson;
        int r = tr[u].rson;
        int top = tr[u].last;
        if (root[top])
        {
            q.push((pii){len + tr[root[top]].val, root[top]});
        }
        if (l)
        {
            q.push((pii){len + tr[l].val - tr[u].val, l});
        }
        if (r)
        {
            q.push((pii){len + tr[r].val - tr[u].val, r});
        }
    }
    return cnt;
}
using namespace std;
int main()
{
    cin >> n >> m >> E;
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        double w;
        cin >> u >> v >> w;
        if (u == n)
        {
            i--;
            m--;
            continue;
        }
        road[u].push_back((node){i, v, w});
        rroad[v].push_back((node){i, u, w});
    }
    dij();
    dfs(n);
    build();
    cout<<kshort();
    return 0;
}