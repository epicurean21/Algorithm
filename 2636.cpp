/**
 * 2636: 치즈
 * DFS, BFS, Simulation
 */
#include <iostream>
#include <vector>
#include <queue>

using namespace std;
#define MAX 101
int N, M, map[MAX][MAX], dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1}, cnt, ans, ans2;
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
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            chk[i][j] = false;
            air_chk[i][j] = false;
        }
    }
}

void isPossible(int x, int y) { // 치즈 내부 공기인지 확인
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
            if (nx < 0 || nx > M - 1 || ny < 0 || ny > N - 1) continue;
            if (map[ny][nx]) continue;
            if (air_chk[ny][nx]) continue;
            air_chk[ny][nx] = true;
            q.push({nx, ny});
        }
    }
}

void dfs(int x, int y) {
    chk[y][x] = true;
    int side_cnt = 0;
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx < 0 || nx >= M || ny < 0 || ny >= N) continue;

        if (map[ny][nx] && !chk[ny][nx])
            dfs(nx, ny);

        if (chk[ny][nx]) continue;
        if (air_chk[ny][nx]) // 외부 공기인지 내부 공기인지 확인
            side_cnt++;

    }

    if (side_cnt) {
        map[y][x] = 0;
        cnt--;
    }
}

void chk_air() {
    for (int i = 0; i < M; i++) {
        if (!air_chk[0][i])
            isPossible(i, 0);
        if (!air_chk[N - 1][i])
            isPossible(i, N - 1);
    }
    for (int i = 0; i < N; i++) {
        if (!air_chk[i][0])
            isPossible(0, i);
        if (!air_chk[i][M - 1])
            isPossible(M - 1, i);
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

    ans2 = cnt;
    while (cnt) {
        init();
        ans++;
        //print_map();
        chk_air();
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                if (map[i][j] && !chk[i][j])
                    dfs(j, i);

        if (cnt) ans2 = cnt;
    }

    cout << ans << '\n' << ans2 << '\n';
    return 0;
}