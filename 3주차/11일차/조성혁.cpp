#include <iostream>
#include <algorithm>

using namespace std;

int dp[101][10002];

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);

	int n, k;
	cin >> n >> k;

	int beforeFirstMax = 0;
	int beforeSecondMax = 0;
	for (int i = 1; i <= n; i++) {
		int curFirstMax = 0;
		int curSecondMax = 0;
		for (int j = 1; j <= k; j++) {
			int x;
			cin >> x;

			if (dp[i - 1][j] == beforeFirstMax) {
				dp[i][j] = beforeSecondMax + x;
			}
			else {
				dp[i][j] = beforeFirstMax + x;
			}

			if (curFirstMax <= dp[i][j]) {
				curSecondMax = curFirstMax;
				curFirstMax = dp[i][j];
			}
			else if (curSecondMax <= dp[i][j] && dp[i][j] < curFirstMax) {
				curSecondMax = dp[i][j];
			}
		}

		beforeFirstMax = curFirstMax;
		beforeSecondMax = curSecondMax;
	}

	int ans = 0;
	for (int i = 1; i <= k; i++) {
		ans = max(ans, dp[n][i]);
	}

	cout << ans;
}
