#include <bits/stdc++.h>
using namespace std;

int n;
bool flag = false;

bool check(string s){
    int size = s.size();
    for(int i=1;i<=size/2;i++){
        int n1 = size-1;
        int n2 = size-1-i;
        bool flag = true;
        for(int j=0;j<i;j++){
            if(s[n1-j] != s[n2-j]){
                flag = false;
                break;
            }
        }

        if(flag) return true;
    }
    return false;
}

void dfs(int dep, string s){
    if(flag) return;
    if(dep == n){
        cout << s;
        flag = true;
        return;
    }
    for(int i=1;i<=3;i++){
        char c = '0' + i;
        if(!check(s + c)) dfs(dep+1, s + c);
    }
}

int main(){
    cin.tie(0)->sync_with_stdio(0);

    cin >> n;
    dfs(0,"");

    return 0;
}