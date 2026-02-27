#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

string str;
int K[3000001]; // K[i]: i까지의 K의 등장 횟수
int R[3000001];

int main() {
    // 문자열을 순회하며 K, R의 등장 횟수의 누적 합을 구한다.
    // 구간 [i, j]를 R의 영역이라고 간주할 때(K 섞일 수 있으나, 고려 X),
    // min(K[i-1], K[N]-K[j]) * 2 + R[j] - R[i-1]
    cin>>str;
    for (int i=1;i<=str.size();i++) {
        if (str[i-1]=='K') {
            K[i]=K[i-1]+1;
            R[i]=R[i-1];
        }
        else {
            K[i]=K[i-1];
            R[i]=R[i-1]+1;
        }
    }

    int l=1;
    int r=str.size();
    int ans=0;
    while (l<=r) {
        if (l==r&&str[l-1]=='K') break;

        int left=K[l-1];
        int right=K[str.size()]-K[r];
        ans=max(ans,min(left,right)*2+R[r]-R[l-1]);

        // 왼쪽 K가 더 적었다면 다음 K로 이동
        if (left<right) {
            l++;
            while (l<str.size()&&str[l-1]!='R') l++;
        }
        else {
            r--;
            while (r>=0&&str[r-1]!='R') r--;
        }
    }

    cout<<ans;
}
