#include <bits/stdc++.h>
using namespace std;

// 해당 위치 값
int B[32] = {
    0, 2, 4, 6, 8,
    10, 12, 14, 16, 18,
    20, 22, 24, 26, 28,
    30, 32, 34, 36, 38,
    40, 13, 16, 19, 25,
    26, 27, 28, 22, 24,
    30, 35
};
// i번 나왔을 때 다음 위치
int A[32][5] = {
    {1,2,3,4,5},{2,3,4,5,6},{3,4,5,6,7},{4,5,6,7,8},{5,6,7,8,9},
    {21,22,23,24,30},{7,8,9,10,11}, {8,9,10,11,12},{9,10,11,12,13},{10,11,12,13,14},
    {28,29,24,30,31},{12,13,14,15,16},{13,14,15,16,17},{14,15,16,17,18},{15,16,17,18,19},
    {27,26,25,24,30},{17,18,19,20,32},{18,19,20,32,32},{19,20,32,32,32},{20,32,32,32,32},
    {32,32,32,32,32},{22,23,24,30,31}, {23,24,30,31,20},{24,30,31,20,32},{30,31,20,32,32},
    {24,30,31,20,32},{25,24,30,31,20},{26,25,24,30,31}, {29,24,30,31,20}, {24,30,31,20,32},
    {31,20,32,32,32},{20,32,32,32,32}
};

vector<int> v; // 주사위 정보

void input(){
   v.resize(10); for(int i=0;i<10;i++){cin >> v[i]; v[i]--;}
}

int ans = 0;

vector<int> score(4,0), pos(4,0); // 현재 점수, 현재 위치
void dfs(int dep){
    if(dep == 10){
        int sum = 0;
        for(int i=0;i<4;i++) sum += score[i];
        ans = max(ans, sum);
        return;
    }

    // i번째가 움직임.
    for(int i=0;i<4;i++){
        if(pos[i] == 32) continue;
        int nx_pos = A[pos[i]][v[dep]];
        if(nx_pos == 32){
            int temp = pos[i];
            pos[i] = 32;
            dfs(dep+1);
            pos[i] = temp;
            continue;
        }

        // 현재 위치함.
        bool flag = false;
        for(int j=0;j<4;j++){
            if(pos[j] == nx_pos){
                flag = true;
                break;
            }
        }
        if(flag) continue;
      
        int temp = pos[i];
        pos[i] = nx_pos;
        score[i] += B[nx_pos];
        dfs(dep+1);
        pos[i] = temp;
        score[i] -= B[nx_pos];
    }
}

void solve(){
    dfs(0);
    cout << ans;
}

int main(){
    cin.tie(0)->sync_with_stdio(0);

    input();
    solve();

    return 0;
}