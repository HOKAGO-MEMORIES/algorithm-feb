#include <vector>
#include <iostream>
#include <queue>
#include <stack>
#include <algorithm>
#include <memory.h>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <set>

using namespace std;

void tc() {
	int n, m;
	cin >> n >> m;
	vector<vector<pair<int, int>>>v(n+1);
	for (int i = 0; i < m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		v[a].push_back({ b, c });
		v[b].push_back({ a, c });
	}
	int k;
	cin >> k;
	vector<int> friends;
	for (int i = 0; i < k; i++) {
		int x;
		cin >> x;
		friends.push_back(x);
	}
	priority_queue<pair<int, int>>pq;
	int sums[101] = { 0 };
	for (auto x : friends) {
		int dist[101];
		fill(dist, dist + 101, 2147483647);
		pq.push({ 0, x });
		while (pq.size()) {
			auto f = pq.top();
			pq.pop();
			int ndist = -f.first;
			int nx = f.second;
			if (ndist > dist[nx]) {
				continue;
			}
			dist[nx] = ndist;
			for (auto nb : v[nx]) {
				if (ndist + nb.second > dist[nb.first])continue;
				pq.push({ -ndist - nb.second, nb.first });
			}
		}

		for (int i = 1; i <= n; i++) {
			sums[i] += dist[i];
		}
	}
	int ans = 0;
	int min_value = 2147483647;
	for (int i = 1; i <= n; i++) {
		if (sums[i] < min_value) {
			min_value = sums[i];
			ans = i;
		}
	}

	cout << ans << "\n";
}

int main() {
	cin.tie(0); cout.tie(0); ios_base::sync_with_stdio(0);
	int t;
	cin >> t;
	while (t--)tc();
}
