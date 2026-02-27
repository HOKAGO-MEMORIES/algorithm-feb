#include <bits/stdc++.h>
using namespace std;

struct bridge{
    // 위치(x,y), 연결된 그룹(g1, g2), 연결 가능한 방향(c)
    int x,y,g1,g2;
    char c;
};

int n,m;
int bridge_size, group_size;
int dx[] = {-1,1,0,0}, dy[] = {0,0,-1,1};
char A[738][738];
int B[738][738];
bool visited[738][738];
bool flag; // true면 이미 print()함.
int start_group;
vector<int> parent; // union_find를 위한 parent
set<int> target_groups; // target이 존재하는 그룹
vector<pair<int,int>> Ps, Bs;
pair<int,int> start_pos;
vector<bridge> bridges[18]; // 각 ?(bridge)에 대해서 위치(x,y), 연결된 그룹(g1, g2), 연결 가능한 방향(c) 를 저장
void input(){
    cin >> n >> m;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin >> A[i][j];
            B[i][j] = -1; // B의 초기값
            if(A[i][j] == 'P'){
                Ps.push_back({i,j});
                A[i][j] = '.';
            }
            if(A[i][j] == 'B'){
                Bs.push_back({i,j});
                A[i][j] = '.';
            }
        }
    }

    int x,y; cin >> x >> y;
    x--, y--;
    start_pos = {x,y};
}

void alloc_num_dfs(int x, int y, int num){
    B[x][y] = num;
    for(int i=0;i<4;i++){
        int nx = x + dx[i], ny = y + dy[i];
        if(nx >= 0 && nx < n && ny >= 0 && ny < m && !visited[nx][ny] && A[x][y] == A[nx][ny]){
            visited[nx][ny] = true;
            alloc_num_dfs(nx, ny, num);
        }
    }
}

void alloc_num_to_B(){
    int num = 0;
    int bridge_idx = 0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            // 출발한 곳 할당
            if(i == start_pos.first && j == start_pos.second && !visited[i][j]){
                visited[i][j] = true;
                alloc_num_dfs(i,j,num);
                num++;
            }

            if(A[i][j] == '?'){
                bool can_install_bridge = false;
                
                // South
                if(i-1 >= 0 && i+1 < n && A[i-1][j] == '.' && A[i+1][j] == '1'){
                    can_install_bridge = true;
                    if(B[i-1][j] == -1 && !visited[i-1][j]){
                        visited[i-1][j] = true;
                        alloc_num_dfs(i-1,j,num);
                        num++;
                    }
                    if(B[i+1][j] == -1 && !visited[i+1][j]){
                        visited[i+1][j] = true;
                        alloc_num_dfs(i+1,j,num);
                        num++;
                    }
                    bridges[bridge_idx].push_back({i,j,B[i-1][j], B[i+1][j], 'S'});
                }
                // North
                if(i-1 >= 0 && i+1 < n && A[i-1][j] == '1' && A[i+1][j] == '.'){
                    can_install_bridge = true;
                    if(B[i-1][j] == -1 && !visited[i-1][j]){
                        visited[i-1][j] = true;
                        alloc_num_dfs(i-1,j,num);
                        num++;
                    }
                    if(B[i+1][j] == -1 && !visited[i+1][j]){
                        visited[i+1][j] = true;
                        alloc_num_dfs(i+1,j,num);
                        num++;
                    }
                    bridges[bridge_idx].push_back({i,j,B[i-1][j], B[i+1][j], 'N'});
                }
                // East
                if(j-1 >= 0 && j+1 < m && A[i][j-1] == '.' && A[i][j+1] == '1'){
                    can_install_bridge = true;
                    if(B[i][j-1] == -1 && !visited[i][j-1]){
                        visited[i][j-1] = true;
                        alloc_num_dfs(i,j-1,num);
                        num++;
                    }
                    if(B[i][j+1] == -1 && !visited[i][j+1]){
                        visited[i][j+1] = true;
                        alloc_num_dfs(i,j+1,num);
                        num++;
                    }
                    bridges[bridge_idx].push_back({i,j,B[i][j-1], B[i][j+1], 'E'});
                }
                // West
                if(j-1 >= 0 && j+1 < m && A[i][j-1] == '1' && A[i][j+1] == '.'){
                    can_install_bridge = true;
                    if(B[i][j-1] == -1 && !visited[i][j-1]){
                        visited[i][j-1] = true;
                        alloc_num_dfs(i,j-1,num);
                        num++;
                    }
                    if(B[i][j+1] == -1 && !visited[i][j+1]){
                        visited[i][j+1] = true;
                        alloc_num_dfs(i,j+1,num);
                        num++;
                    }
                    bridges[bridge_idx].push_back({i,j, B[i][j-1], B[i][j+1], 'W'});
                }

                if(can_install_bridge) bridge_idx++;
            }
        }
    }

    group_size = num;
    parent.resize(group_size);
    for(int i=0;i<group_size;i++) parent[i] = i;
    // cout << "num : " << num << "\n";
    bridge_size = bridge_idx;
    // cout << "bridge size : " << bridge_size << "\n"; 

    // bridges 출력.
    // for(int i=0;i<bridge_idx;i++){
    //     for(int j=0;j<bridges[i].size();i++){
    //         cout << bridges[i][j].x << " " << bridges[i][j].y << " " <<bridges[i][j].g1 << " " <<bridges[i][j].g2 << " " <<bridges[i][j].c << "\n";
    //     }
    // }

    // target('B', 'P')가 어떤 그룹에 속하는 지를 확인
    for(int i=0;i<Bs.size();i++){
        if(B[Bs[i].first][Bs[i].second] != -1) target_groups.insert(B[Bs[i].first][Bs[i].second]);
    }
    for(int i=0;i<Ps.size();i++){
        if(B[Ps[i].first][Ps[i].second] != -1) target_groups.insert(B[Ps[i].first][Ps[i].second]);
    }

    // start가 어떤 그룹에 속하는 지를 확인
    start_group = B[start_pos.first][start_pos.second];
}

void print(){
    // '.'로 만들었던 target들 출력을 위해서 다시 원복
    for(int i=0;i<Bs.size();i++){
        A[Bs[i].first][Bs[i].second] = 'B';
    }
    for(int i=0;i<Ps.size();i++){
        A[Ps[i].first][Ps[i].second] = 'P';
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(A[i][j] == '?') cout << 'E';
            else cout << A[i][j];
        }
        cout << "\n";
    }
}

int find(int a){
    if(a == parent[a]) return a;
    return find(parent[a]);
}

bool check_connect(){
    for(auto k : target_groups){
        if(find(k) == find(start_group)) return true;
    }
    return false;
}

void dfs_bridge(int dep){
    if(flag) return;
    if(dep == bridge_size){
        if(check_connect()){
            print();
            flag = true;
        }
        return;
    }
    
    for(int i=0;i<bridges[dep].size();i++){
        bridge cur = bridges[dep][i];
        int p1 = find(cur.g1), p2 = find(cur.g2);
        bool is_merged = false;
        if(p1 != p2){
            is_merged = true;
            if(p1 > p2) swap(p1, p2);
            parent[p1] = p2;
        }

        A[cur.x][cur.y] = cur.c;

        dfs_bridge(dep+1);

        if(is_merged){
            parent[p1] = p1;
        }
    }
}

void solve(){
    alloc_num_to_B();
    // B값 출력
    // for(int i=0;i<n;i++){
    //     for(int j=0;j<m;j++){
    //         cout << B[i][j] << " ";
    //     }
    //     cout << "\n";
    // }
    if(start_group == -1){
        cout << -1;
        return;
    }
    dfs_bridge(0);
    if(!flag) cout << -1;
}

int main(){
    cin.tie(0)->sync_with_stdio(0);

    input();
    solve();

    return 0;
}