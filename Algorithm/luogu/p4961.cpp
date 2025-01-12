// P4961 小埋与扫雷
#include <bits/stdc++.h>
using namespace std;
int n,m;
int a[1001][1001];//0:未标记 1:雷 2:空格 3:数字
bool tag[1001][1001];//标记空
int py[]={-1,-1,-1,0,1,1,1,0},px[]={-1,0,1,1,1,0,-1,-1};//位移数组

void idfy(int y,int x)
{
	bool lei=false;//判断四周是否有雷
	for(int i=0;i<8&&!lei;i++)
	{
		int yy=y+py[i];
		int xx=x+px[i];
		if(yy>0&&yy<=n&&xx>0&&xx<=m)
			if(a[yy][xx]==1)
				lei=true;
	}
	if(!lei)//空格
		a[y][x]=2;
	else//数字
		a[y][x]=3;
	return;
}

void dfs(int y,int x)
{
	tag[y][x]=true;
	for(int i=0;i<8;i++)
	{
		int yy=y+py[i];
		int xx=x+px[i];
		if(yy>0&&yy<=n&&xx>0&&xx<=m)
			if(a[yy][xx]==2&&tag[yy][xx]==false)
				dfs(yy,xx);
	}
	return; 
}

bool check(int y,int x)
{
	bool ans=true;
	for(int i=0;i<8&&ans==true;i++)
	{
		int yy=y+py[i];
		int xx=x+px[i];
		if(yy>0&&yy<=n&&xx>0&&xx<=m)
			if(a[yy][xx]==2)
				ans=false;
	}
	return ans;
}

int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			cin>>a[i][j];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(!a[i][j])
				idfy(i,j);
	int cnt=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(a[i][j]==2&&!tag[i][j])
			{
			 
				dfs(i,j),cnt++;//计数:空
			} 
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(a[i][j]==3)
				if(check(i,j))cnt++;//计数:周围八格没有“空格”的“数字”个数
	cout<<cnt<<endl;
	return 0;
}