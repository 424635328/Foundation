//P2240 【深基12.例1】部分背包问题
#include<bits/stdc++.h>
#include<algorithm>
using namespace std;

typedef struct heap{
    float weight;
    float value;
    float power;
}heap;
int N,T;

int main(){
    cin>>N>>T;
    float w,v;
    heap coins[N];
    for(int i=0;i<N;i++){
        cin>>w>>v;
        coins[i].weight=w;
        coins[i].value=v;
        coins[i].power=coins[i].value/coins[i].weight;
    }
    for(int i=0;i<N-1;i++){
        for(int j=i+1;j<N;j++){
            if(coins[i].power<coins[j].power){
                swap(coins[i],coins[j]);
            }
        }
    }
    w=0;v=0;
    for(int i=0;i<N;i++){
        if(w+coins[i].weight<=T){
            w+=coins[i].weight;
            v+=coins[i].value;
        }
        if(w+coins[i].weight>T){
            v+=(T-w)*coins[i].power;
            break;
        }
    }
    printf("%.2f",v);
    return 0;
}