//question : https://icpc.me/11062
#include <bits/stdc++.h>
#define INT_MAX 2147483647
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
typedef pair<ll,ll> llll;
typedef pair<int,int> ii;

int cards [1001];
int dp[1001][1001];
int n;

int dfs(int s, int e){
    if(dp[s][e]!=-1)return dp[s][e];
    bool turn = (n-(e-s))&1;
    int f = (turn?cards[s]:0);
    int b = (turn?cards[e]:0);
    if(s==e){
        return dp[s][e]=f;
    }
    if(turn){
        return dp[s][e] = max(dfs(s+1, e)+f, dfs(s, e-1)+b);
    }else{
        return dp[s][e] = min(dfs(s+1, e)+f, dfs(s, e-1)+b);
    }
}

void tc(){
    cin>>n;
    int s=0;
    int e=n-1;
    memset(dp, -1, sizeof dp);
    for(int i=0;i<n;i++){
        cin>>cards[i];
    }

    
    cout<<dfs(s, e)<<"\n";

}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    
    int t;
    cin>>t;
    while(t--)tc();
}