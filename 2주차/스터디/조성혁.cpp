#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

int A[5001];
int L[5001];

int dp[5001][5001]; // dp[i][j] = k : i번째 공격을 마쳤을 때 남은 라이프는 j, 가능한 최대 오라는 k
pair<int, char> rev[5001][5001]; // rev[i][j] = {idx, cmd} : dp[i][j]에서 이전 j는 idx, 공격은 cmd

int main() {
	int n, a, l;
	cin >> n >> a >> l;

	for (int i = 1; i <= n; i++) {
		cin >> A[i] >> L[i];
	}

	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= l; j++) {
			dp[i][j] = -1;
		}
	}

	dp[0][l] = a;

	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= l; j++) {
			// 도달 불가능한 경우
			if (dp[i - 1][j] == -1) continue;

			// 오라 공격 받는 경우
			if (L[i] == -1) {
				dp[i][j] = max(0, dp[i - 1][j] - A[i]);
				rev[i][j] = { j,'A' };
			}

			// 라이프 공격 받는 경우
			else if (A[i] == -1) {
				if (j - L[i] > 0) {
					if (dp[i][j - L[i]] < dp[i - 1][j]) {
						dp[i][j - L[i]] = dp[i - 1][j];
						rev[i][j - L[i]] = { j,'L' };
					}
				}
			}

			// 복합 공격
			else {
				// 현재 오라가 더 작은 경우 라이프로 데미지를 받는다.
				if (dp[i - 1][j] < A[i]) {
					if (j - L[i] > 0) {
						if (dp[i][j - L[i]] < dp[i - 1][j]) {
							dp[i][j - L[i]] = dp[i - 1][j];
							rev[i][j - L[i]] = { j,'L' };
						}
					}
				}
				else {
					// 오라로 받기
					dp[i][j] = dp[i - 1][j] - A[i];
					rev[i][j] = { j,'A' };

					// 라이프로 받기
					if (j - L[i] > 0) {
						if (dp[i][j - L[i]] < dp[i - 1][j]) {
							dp[i][j - L[i]] = dp[i - 1][j];
							rev[i][j - L[i]] = { j,'L' };
						}
					}
				}
			}
		}
	}

	int cj = -1;
	for (int i = 1; i <= l; i++) {
		if (dp[n][i] != -1) {
			cj = i;
			break;
		}
	}

	if (cj == -1) cout << "NO";
	else {
		cout << "YES\n";
		string ans = "";
		for (int i = n; i >= 1; i--) {
			ans += rev[i][cj].second;
			cj = rev[i][cj].first;
		}

		reverse(ans.begin(), ans.end());
		cout << ans;
	}
}
