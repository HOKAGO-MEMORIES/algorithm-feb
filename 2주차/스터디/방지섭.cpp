#include <bits/stdc++.h>
using namespace std;

int main(){
    cin.tie(0)->sync_with_stdio(0);

    int n,a,l; cin >> n >> a >> l;
    vector<pair<int,int>> v(n);
    for(int i=0;i<n;i++) cin >> v[i].first >> v[i].second;
    int dp[n+1][l+1]; for(int i=0;i<n+1;i++) for(int j=0;j<l+1;j++) dp[i][j] = -1;
    dp[0][l] = a;

    for(int i=0;i<n;i++){
        int x = v[i].first, y = v[i].second;
        // /$-$/$Y_i$」: 무조건 라이프에 $Y$ 데미지를 받습니다.
        if(x == -1){
            for(int j=1;j<=l;j++){
                if(dp[i][j] == -1) continue;
                if(j-y >0) dp[i+1][j-y] = max(dp[i+1][j-y],dp[i][j]);
            }
        }
        // 「$X_i$/$-$」: 무조건 오라에 $X$ 데미지를 받습니다. 공격을 받았을 때 오라가 $0$ 미만이 될 경우, $0$으로 회복됩니다.
        else if(y == -1){
            for(int j=1;j<=l;j++){
                if(dp[i][j] == -1) continue;
                dp[i+1][j] = max(dp[i+1][j], max(0, dp[i][j] - x));
            }
        }
        // 「$X_i$/ $Y_i$」: 현재 오라가 $X$보다 작을 경우, 무조건 라이프에 $Y$ 데미지를 받습니다
        else{
            for(int j=1;j<=l;j++){
                if(dp[i][j] == -1) continue;
                if(dp[i][j] < x){
                    if(j-y > 0) dp[i+1][j-y] = max(dp[i+1][j-y], dp[i][j]); // 오라가 x보다 작을 경우
                }
                else{
                    dp[i+1][j] = max(dp[i+1][j], dp[i][j] - x); // 오라로 막기
                    if(j-y >0) dp[i+1][j-y] = max(dp[i+1][j-y],dp[i][j]); // 라이프로 막기
                }
            }
        }
    }

    for(int i=1;i<=l;i++){
        if(dp[n][i] != -1){
            cout << "YES\n";
            // 역추적 시작
            vector<char> retrack;
            int cur_x = n, cur_y = i;
            while(cur_x != 0){
                int x = v[cur_x-1].first, y = v[cur_x-1].second;
                // /$-$/$Y_i$」: 무조건 라이프에 $Y$ 데미지를 받습니다.
                if(x == -1){
                    cur_y += y;
                    retrack.push_back('L');
                }
                // 「$X_i$/$-$」: 무조건 오라에 $X$ 데미지를 받습니다. 공격을 받았을 때 오라가 $0$ 미만이 될 경우, $0$으로 회복됩니다.
                else if(y == -1){
                    // 그냥 위로 올라감
                    retrack.push_back('A');
                }
                // 「$X_i$/ $Y_i$」: 현재 오라가 $X$보다 작을 경우, 무조건 라이프에 $Y$ 데미지를 받습니다
                else{
                    if(cur_y + y <= l &&dp[cur_x-1][cur_y+y] == dp[cur_x][cur_y]) // 라이프 공격 맞고 내려와서 오라는 똑같음.
                    {
                        cur_y += y;
                        retrack.push_back('L');
                    }
                    else{ // 오라 공격 맞음.
                        retrack.push_back('A');
                    }
                }
                cur_x--;
            }
            for(int i=n-1;i>=0;i--) cout << retrack[i];

            return 0;
        }
    }
    cout << "NO";


    return 0;
}