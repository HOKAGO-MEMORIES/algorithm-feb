#include <iostream>
#include <vector>
#include <queue>

#define SIZE 739

using namespace std;

struct Change {
    int node, p, r; // 노드 번호, parent, rank
    bool ht; // hasTar
};

struct Cand {
    char dir;
    int a, b; // 두 영역 번호
};

int n, m, sx, sy;
char board[SIZE][SIZE];
int region[SIZE][SIZE];
vector<pair<int, int>> pos; // ? 좌표
vector<pair<int, int>> tar; // B, P 좌표
int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0,-1 };
char dir[4] = { 'N','E','S','W' };
int parent[SIZE * SIZE]; // 영역 번호, 부모
int rnk[SIZE * SIZE];
int isHigh[SIZE * SIZE];
bool hasTar[SIZE * SIZE];
vector<Change> history;
vector<Cand> cands[18];
int startRegion;

int Find(int x) {
    while (parent[x] != x) x = parent[x];

    return x;
}

// 실제로 합쳐졌다면 true
bool Union(int x, int y) {
    int px = Find(x);
    int py = Find(y);

    if (px == py) {
        history.push_back({ px,parent[px],rnk[px],hasTar[px] });
        history.push_back({ py,parent[py],rnk[py],hasTar[py] });
        return false;
    }
    if (rnk[px] < rnk[py]) swap(px, py);
    history.push_back({ px,parent[px],rnk[px],hasTar[px] });
    history.push_back({ py,parent[py],rnk[py],hasTar[py] });
    parent[py] = px;
    hasTar[px] = hasTar[px] || hasTar[py];
    if (rnk[px] == rnk[py]) rnk[px]++;
    return true;
}

void rollback() {
    Change cy = history.back();
    history.pop_back();
    Change cx = history.back();
    history.pop_back();

    parent[cx.node] = cx.p;
    rnk[cx.node] = cx.r;
    hasTar[cx.node] = cx.ht;
    parent[cy.node] = cy.p;
    rnk[cy.node] = cy.r;
    hasTar[cy.node] = cy.ht;
}

bool connected() {
    return hasTar[Find(startRegion)];
}

void printBoard() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (board[i][j] == '?') cout << 'N';
            else cout << board[i][j];
        }
        cout << "\n";
    }
}

// ?에 대해 유효한 경사로를 설치한다.
void dfs(int cnt) {
    if (cnt == pos.size()) {
        if (connected()) {
            printBoard();
            exit(0);
        }

        return;
    }

    if (cands[cnt].empty()) {
        dfs(cnt + 1);

        return;
    }

    int x = pos[cnt].first;
    int y = pos[cnt].second;

    for (auto e : cands[cnt]) {
        board[x][y] = e.dir;
        bool merged = Union(e.a, e.b);
        if (merged && connected()) {
            printBoard();
            exit(0);
        }

        dfs(cnt + 1);
        rollback();
        board[x][y] = '?';
    }
}

int main() {
    cin.tie(0);
    ios::sync_with_stdio(0);

    // 먼저 모든 좌표에 대해 BFS를 돌며 독립된 영역을 넘버링한다.
    // 이후 ?에 대해 가능한 조합들을 생성한다.
    // 이후 모든 ?에 대해 (a)를 만족하면 Union한다.
    // B, P가 속한 영역과 시작 좌표의 parent가 같은 영역에 있다면 답을 출력한다.

    cin >> n >> m;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> board[i][j];
            if (board[i][j] == '?') pos.push_back({ i,j });
            else if (board[i][j] == 'B' || board[i][j] == 'P') tar.push_back({ i,j });
        }
    }

    int regionCounter = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (board[i][j] == '#' || board[i][j] == '?') continue;
            if (region[i][j] != 0) continue;

            int counter = ++regionCounter;
            region[i][j] = counter;
            isHigh[counter] = (board[i][j] == '1');
            queue<pair<int, int>> q;
            q.push({ i,j });

            while (!q.empty()) {
                int x = q.front().first;
                int y = q.front().second;
                q.pop();

                for (int idx = 0; idx < 4; idx++) {
                    int nx = x + dx[idx];
                    int ny = y + dy[idx];

                    if (nx < 0 || ny < 0 || nx >= n || ny >= m) continue;
                    if (board[nx][ny] == '?' || board[nx][ny] == '#') continue;

                    // 원하는 문자가 아닌 경우
                    if (!isHigh[counter]) {
                        if (board[nx][ny] == '1') continue;
                    }
                    else {
                        if (board[nx][ny] != '1') continue;
                    }

                    // 이미 탐색한 경우
                    if (region[nx][ny] != 0) continue;

                    region[nx][ny] = counter;
                    q.push({ nx,ny });
                }
            }
        }
    }

    for (int idx = 0; idx < pos.size(); idx++) {
        int x = pos[idx].first;
        int y = pos[idx].second;

        for (int i = 0; i < 4; i++) {
            int j = (i + 2) % 4;
            int ax = x + dx[i];
            int ay = y + dy[i];
            int bx = x + dx[j];
            int by = y + dy[j];
            char curDir = dir[i];

            if (ax < 0 || ax >= n || ay < 0 || ay >= m) continue;
            if (bx < 0 || bx >= n || by < 0 || by >= m) continue;

            int ra = region[ax][ay];
            int rb = region[bx][by];

            if (!ra || !rb) continue; // 벽이나 ?인 경우
            if (isHigh[ra] && !isHigh[rb]) {
                bool duplicated = false;
                for (auto e : cands[idx]) {
                    if (e.a == ra && e.b == rb) {
                        duplicated = true;
                        break;
                    }
                }

                if (!duplicated) {
                    cands[idx].push_back({ curDir,ra,rb });
                }
            }
        }
    }

    for (int i = 1; i <= regionCounter; i++) {
        parent[i] = i;
    }

    for (auto e : tar) {
        hasTar[region[e.first][e.second]] = true;
    }

    cin >> sx >> sy;

    startRegion = Find(region[sx - 1][sy - 1]);

    if (tar.empty()) {
        cout << -1;
        return 0;
    }

    if (connected()) {
        printBoard();
        return 0;
    }

    dfs(0);
    cout << -1;
}
