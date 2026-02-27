#include <bits/stdc++.h>
using namespace std;

void solve(){
    int n,m; cin >> n >> m;
    int dis[n+1][n+1];
    // 초기화
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(i == j) dis[i][j] = 0;
            else dis[i][j] = 1000000000;
        }
    }

    // 간선 입력
    for(int i=0;i<m;i++){
        int a,b,c; cin >> a >> b >> c;
        dis[a][b] = c;
        dis[b][a] = c;
    }

    // 플로이드 워셜
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            for(int k=1;k<=n;k++){
                dis[j][k] = min(dis[j][k], dis[j][i] + dis[i][k]);
            }
        }
    }

    // for(int i=1;i<=n;i++){
    //     for(int j=1;j<=n;j++){
    //         cout << dis[i][j] << " ";
    //     }
    //     cout << "\n";
    // }

    int k; cin >> k;
    int friends[k]; for(int i=0;i<k;i++) cin >> friends[i];

    int mn = INT32_MAX;
    int ans = -1;
    for(int i=1;i<=n;i++){
        int sum = 0;
        for(int j=0;j<k;j++){
            sum += dis[i][friends[j]];
        }
        if(sum < mn){
            ans = i;
            mn = sum;
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(0)->sync_with_stdio(0);

    int t; cin >> t;
    while(t--){
        solve();
    }

    return 0;
}