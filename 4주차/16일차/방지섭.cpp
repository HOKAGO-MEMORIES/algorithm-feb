#include <bits/stdc++.h>
using namespace std;

string s;
int s_size;
void input(){
    cin >> s;
    s_size = s.size();
}

void solve(){
    s = ' ' + s; // 앞에 빈칸 추가해서 누적합과 idx 맞추기.
    int R[s_size+1], K[s_size+1];
    R[0] = 0, K[0] = 0; // R[i] : 0부터 i번째까지의 R의 개수
    for(int i=1;i<=s_size;i++){
        if(s[i] == 'R'){
            R[i] = R[i-1] + 1;
            K[i] = K[i-1];
        }
        else{
            R[i] = R[i-1];
            K[i] = K[i-1] + 1;
        }
    }
    int i = 1, j = s_size; // 현재 시작, 끝

    int ans = 0;
    if(R[j] - R[i-1] > 0) ans = (R[j] - R[i-1]) + min(K[i-1], K[s_size]-K[j]) * 2;
    while(i <= j){
        while(s[i] != 'K'){
            i++;
            if(i > s_size) break;
        }
        i++;
        while(s[j] != 'K'){
            j--;
            if(j < 0) break;
        }
        j--;

        if(i > j) break;

        if(R[j] - R[i-1] > 0) ans = max(ans, (R[j] - R[i-1]) + min(K[i-1], K[s_size]-K[j]) * 2);
    }
    

    cout << ans;
}

int main(){
    cin.tie(0)->sync_with_stdio(0);

    input();
    solve();

    return 0;
}