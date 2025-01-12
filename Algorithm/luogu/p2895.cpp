// P2895 [USACO08FEB] Meteor Shower S
#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 305;
const int INF = 1e9;
int n, x, y, t, ma[MAX_N][MAX_N], vis[MAX_N][MAX_N];
struct Point
{
    int x, y, t;
} p[50000];

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

void bfs(){
    int t=0,w=1;
    vis[0][0]=1;
    while(t<w)
    {
        int x=p[t].x,y=p[t].y,time=p[t].t;
        t++;
        for(int i=0;i<4;i++)
        {
            int nx=x+dx[i],ny=y+dy[i];
            if(vis[nx][ny]||nx<0||ny<0||time+1>=ma[nx][ny]) continue;
            if(ma[nx][ny]==INF)
            {
                cout<<time+1;
                return;
            }
            p[w].x=nx,p[w].y=ny,p[w++].t=time+1;
            vis[nx][ny]=1;
        }
    }
	cout<<"-1"<<endl;
}

int main()
{
    memset(vis,0,sizeof(vis));
    for (int i = 0; i <= MAX_N; i++) //
        for (int j = 0; j <= MAX_N; j++)
            ma[i][j] = INF;
    cin >> n;
    for(int i=0;i<n;i++){
        cin>>x>>y>>t;
        ma[x][y]=min(ma[x][y],t);
        for(int j=0;j<4;j++)
        {
            int nx=x+dx[j],ny=y+dy[j];
            if(nx<0 || ny<0) continue;
            ma[nx][ny]=min(ma[nx][ny],t);
        }

    }
    bfs();

    return 0;
}