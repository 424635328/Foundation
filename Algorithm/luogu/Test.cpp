#include <bits/stdc++.h>
#include <algorithm>
using namespace std;
vector<vector<int>> data;
vector<vector<int>> dp;
int main()
{
    int rows;
    cin >> rows;
    for (int i = 0; i < rows; i++)
    {
        vector<int> row;
        for(int j=0;j<=i;j++){
            int temp;
            cin>>temp;
            row.push_back(temp);
        }
        data.push_back(row);
    }
     // 初始化 dp 数组
    dp.resize(rows);
    for (int i = 0; i < rows; i++) {
        dp[i].resize(i + 1);
    }
    dp[0][0]=data[0][0];
    for(int i=1;i<rows;i++){
        for(int j=0;j<=i;j++){
            if(j==0)  dp[i][j]= dp[i-1][j]+data[i][j];
            else if(j==i) dp[i][j]= dp[i-1][j-1]+data[i][j];
            else dp[i][j]= max(dp[i-1][j],dp[i-1][j-1])+data[i][j];
        }
    }
    int ma=0;
    for(int i=0;i<rows;i++){
        
        ma=max(dp[rows-1][i],ma);
    }
    cout<<ma;
    return 0;
}