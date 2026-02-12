#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

int dice[10]; // 주사위
int ans;
map<int, pair<int, int>> pos; // 말의 위치, pos[num] = {i, j}, routes[i][j] 위치에 num이 있다.
vector<int> routes[5]; // 0, 10, 20, 30, 25에서 시작하는 경로

void dfs(int cnt, int score) {
	if (cnt == 10) {
		ans = max(ans, score);

		return;
	}

	for (int i = 0; i < 4; i++) {
		int idx1 = pos[i].first;
		int idx2 = pos[i].second;

		// 탈출한 말이면 다음 말이 이동하도록
		if (idx1 == -1 && idx2 == -1) continue;

		// 이동
		int nextIdx2 = idx2 + dice[cnt];

		// 인덱스 벗어나면 탈출
		if (nextIdx2 >= routes[idx1].size()) {
			pos[i].first = -1;
			pos[i].second = -1;

			dfs(cnt + 1, score);

			// 인덱스 원복
			pos[i].first = idx1;
			pos[i].second = idx2;
		}
		else {
			int newIdx1 = idx1;
			int newIdx2 = nextIdx2;

			// 경로 보정
			// route0에서 10, 20, 30을 밟은 경우 경로 수정
			if (newIdx1 == 0 && (routes[newIdx1][newIdx2] == 10 || routes[newIdx1][newIdx2] == 20 || routes[newIdx1][newIdx2] == 30)) {
				newIdx1 = routes[newIdx1][newIdx2] / 10;
				newIdx2 = 0;
			}
			// route0, 10, 20, 30에서 25, 30, 35, 40을 밟은 경우 경로 수정
			else if ((1 <= newIdx1 && newIdx1 <= 3 && routes[newIdx1][newIdx2] % 5 == 0 && 25 <= routes[newIdx1][newIdx2] && routes[newIdx1][newIdx2] <= 35) || (0 <= newIdx1 && newIdx1 <= 3 && routes[newIdx1][newIdx2] == 40)) {
				newIdx2 = routes[newIdx1][newIdx2] / 5 - 5;
				newIdx1 = 4;
			}

			// 다른 말이 있으면 안 된다. 도착 지점 제외
			bool able = true;
			for (int j = 0; j < 4; j++) {
				if (i == j) continue;
				if (pos[j].first == -1 && pos[j].second == -1) continue;

				if (newIdx1 == pos[j].first && newIdx2 == pos[j].second) {
					able = false;
					break;
				}
			}

			if (able) {
				pos[i].first = newIdx1;
				pos[i].second = newIdx2;

				dfs(cnt + 1, score + routes[newIdx1][newIdx2]);

				// 인덱스 원복
				pos[i].first = idx1;
				pos[i].second = idx2;
			}
		}
	}
}

int main() {
	for (int i = 0; i < 10; i++) {
		cin >> dice[i];
	}

	vector<int> route0, route10, route20, route30, route25;

	// 출발지는 0
	for (int i = 0; i <= 20; i++) {
		route0.push_back(i * 2);
	}

	route10 = { 10,13, 16, 19,25,30,35,40 };
	route20 = { 20,22,24,25,30,35,40 };
	route30 = { 30,28,27,26,25,30,35,40 };
	route25 = { 25, 30, 35, 40 };

	routes[0] = route0;
	routes[1] = route10;
	routes[2] = route20;
	routes[3] = route30;
	routes[4] = route25;

	// 초기
	for (int i = 0; i < 4; i++) {
		pos[i] = { 0,0 };
	}

	dfs(0, 0);

	cout << ans;
}
