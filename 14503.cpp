#include <iostream>

using namespace std;
#define MAX 52
int N, M, map[MAX][MAX], r, c, d, cnt;
bool clear[MAX][MAX], over;
int dx[] = {0, 1, 0, -1}, dy[] = {-1, 0, 1, 0};

int turn_around(int dir) {
    switch (dir) {
        case 0:
            return 2;
        case 1:
            return 3;
        case 2:
            return 0;
        case 3:
            return 1;
    }
}

void dfs(int x, int y, int dir) {
    if (over)return;
    if (!clear[y][x] && map[y][x] == 0) {
        clear[y][x] = true; // 현 위치 청소
        cnt++; // 개수 증가
    }

    int nd = dir;
    for (int i = 1; i <= 4; i++) { // 4 방향 탐색
        nd -= 1;
        if (nd == -1) nd = 3;
        int nx = x + dx[nd], ny = y + dy[nd];
        if (nx >= M || nx < 0 || ny >= N || nx < 0) continue;
        if (!clear[ny][nx] && map[ny][nx] == 0) {
            dfs(nx, ny, nd);
        }
        if (over)
            return;
    }

    // 4 방향 모두 청소할 대가 없거나 벽임
    nd = turn_around(dir);
    int nx = x + dx[nd], ny = y + dy[nd];
    if (map[ny][nx] != 1 && clear[ny][nx])
        dfs(nx, ny, dir);
    over = true;
    return;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N >> M >> r >> c >> d;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> map[i][j];
            if (map[i][j] == 1)
                clear[i][j] = true;
        }
    }

    dfs(c, r, d);
    cout << cnt << "\n";
    return 0;
}