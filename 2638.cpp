/**
 * 2638: 치즈
 * DFS, BFS, Simulation
 */
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;
#define MAX 101
int N, M, map[MAX][MAX], dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1}, cnt, ans;
bool chk[MAX][MAX], air_chk[MAX][MAX];

void print_map() {
    cout << "\n----------print_map, cur_ans: " << ans << "----------\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++)
            cout << map[i][j] << " ";
        cout << "\n";
    }
    cout << "\n";
}

void init() {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            chk[i][j] = false;
}

bool isPossible(int x, int y) { // 치즈 내부 공기인지 확인
    memset(air_chk, false, sizeof(air_chk));
    queue<pair<int, int>> q;
    air_chk[y][x] = true;
    q.push({x, y});

    while (!q.empty()) {
        int cx = q.front().first;
        int cy = q.front().second;
        q.pop();

        for (int i = 0; i < 4; i++) {
            int nx = cx + dx[i];
            int ny = cy + dy[i];

            if (nx < 0 || nx >= M || ny < 0 || ny >= N) return true;
            if (map[ny][nx]) continue;
            if (air_chk[ny][nx]) continue;
            air_chk[ny][nx] = true;
            q.push({nx, ny});
        }
    }
    return false;
}

void dfs(int x, int y) {
    chk[y][x] = true;
    int side_cnt = 0;
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (nx < 0 || nx >= M || ny < 0 || ny >= N) continue;
        if (map[ny][nx] && !chk[ny][nx]) {
            dfs(nx, ny);
        }
        if (chk[ny][nx]) continue;

        if (isPossible(nx, ny))
            side_cnt++;
    }
    if (side_cnt >= 2) {
        map[y][x] = 0;
        cnt--;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> map[i][j];
            if (map[i][j]) cnt++;
        }
    }

    if (cnt == 0) {
        cout << "0\n";
        return 0;
    }

    while (cnt) {
        init();
        //print_map();
        ans++;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (map[i][j] && !chk[i][j]) {
                    dfs(j, i);
                }
            }
        }
    }

    cout << ans << '\n';
    return 0;
}