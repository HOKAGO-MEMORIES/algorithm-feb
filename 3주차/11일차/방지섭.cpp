#include <bits/stdc++.h>
using namespace std;

int n,m;
int A[100][10000], dp[100][10000];
void input(){
    cin >> n >> m;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin >> A[i][j];
        }
    }
}

void solve(){
    for(int i=0;i<m;i++) dp[0][i] = A[0][i];
    for(int i=1;i<n;i++){
        vector<int> temp(m); for(int j=0;j<m;j++) temp[j] = dp[i-1][j];
        sort(temp.begin(), temp.end(), greater<int>());
        for(int j=0;j<m;j++){
            if(temp[0] == dp[i-1][j]){ // 이전 고양이가 현재 리본을 달 때 만족도가 최고임.
                dp[i][j] = temp[1] + A[i][j]; // 현재 리본은 연속으로 못다니 다음으로 큰 경우에 대해 현재 만족도를 더해줌.
            }
            else{
                dp[i][j] = temp[0] + A[i][j];
            }
        }
    }
    // for(int i=0;i<n;i++){
    //     for(int j=0;j<m;j++){
    //         cout << dp[i][j] << " ";
    //     }
    //     cout << "\n";
    // }

    int ans = 0;
    for(int i=0;i<m;i++) ans = max(ans, dp[n-1][i]);
    cout << ans;
}

int main(){
    cin.tie(0)->sync_with_stdio(0);

    input();
    solve();

    return 0;
}