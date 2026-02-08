#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

#define INF 2e9

using namespace std;

vector<pair<int, int>> graph[1001]; // {노드, 가중치}
vector<pair<int, int>> edges;
int dist[1001];
int delay[1001];

int main() {
	cin.tie(0);
	ios::sync_with_stdio(0);

	int n, m;
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int a, b, c;
		cin >> a >> b >> c;

		graph[a].push_back({ b,c });
		graph[b].push_back({ a,c });

		edges.push_back({ a,b}); // 하나만 저장
	}

	for (int i = 1; i <= n; i++) {
		dist[i] = INF;
		delay[i] = INF;
	}

	// 일단 통제하지 않은 경우 최단 거리를 구한다.
	dist[1] = 0;
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	pq.push({ 0,1 });
	while (!pq.empty()) {
		int w = pq.top().first;
		int node = pq.top().second;
		pq.pop();

		if (dist[node] < w) continue;

		for (int i = 0; i < graph[node].size(); i++) {
			int nnode = graph[node][i].first;
			int nw = graph[node][i].second;

			if (w + nw < dist[nnode]) {
				dist[nnode] = w + nw;
				pq.push({ dist[nnode],nnode });
			}
		}
	}

	int maxVal = 0;
	for (int idx = 0; idx < m; idx++) {
		// 통제할 간선
		int x = edges[idx].first;
		int y = edges[idx].second;

		for (int i = 1; i <= n; i++) {
			delay[i] = INF;
		}

		delay[1] = 0;

		pq.push({ 0,1 });
		while (!pq.empty()) {
			int w = pq.top().first;
			int node = pq.top().second;
			pq.pop();

			if (delay[node] < w) continue;

			for (int i = 0; i < graph[node].size(); i++) {
				int nnode = graph[node][i].first;
				int nw = graph[node][i].second;

				if ((node == x && nnode == y) || (node == y && nnode == x)) continue;

				if (w + nw < delay[nnode]) {
					delay[nnode] = w + nw;
					pq.push({ delay[nnode],nnode });
				}
			}
		}

		if (delay[n] == INF) {
			cout << -1;
			return 0;
		}

		maxVal = max(maxVal, delay[n]);
	}

	cout << maxVal - dist[n];
}
