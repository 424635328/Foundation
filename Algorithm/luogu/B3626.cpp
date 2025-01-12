#include <bits/stdc++.h>
using namespace std;
int n;
struct node{
	int x,cos;
};
int cost[10000];
void bfs(int n){
    queue<node > q;
    node t;
    t.x=1;t.cos=0;
    q.push(t);
    while(!q.empty()){
        node p=q.front();
        q.pop();
        if()

    }

}
int main()
{
    cin>>n;
    for(int i=0;i<n;i++){
        cost[i]=1e9;
    }
    bfs(n);
    return 0;
}
