#include <iostream>
#include <queue>
#include <cstring>

using namespace std;
#define MAX 101
int N, map[MAX][MAX], maxH, ans;
int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};
bool chk[MAX][MAX];

int max(int a, int b) {
    return a > b ? a : b;
}

void sink(int h) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (map[i][j] <= h) {
                map[i][j] = -1;
                chk[i][j] = true;
            }
        }
    }
}

void bfs(int x, int y) {
    if (map[y][x] == -1) return;
    queue<pair<int, int>> q;
    q.push({x, y});
    while (!q.empty()) {
        int curx = q.front().first;
        int cury = q.front().second;
        q.pop();
        chk[cury][curx] = true;
        for (int i = 0; i < 4; i++) {
            int nx = curx + dx[i];
            int ny = cury + dy[i];

            if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
            if (map[ny][nx] == -1) continue;
            if (chk[ny][nx]) continue;
            chk[ny][nx] = true;
            q.push({nx, ny});
        }
    }

}

int solve(int h) {
    int cnt = 0;
    for (int j = 0; j < N; j++) {
        for (int k = 0; k < N; k++) {
            if (!chk[j][k]) {
                bfs(k, j);
                cnt++;
            }
        }
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> map[i][j];
            maxH = max(maxH, map[i][j]);
        }
    }

    for (int i = 0; i < maxH; i++) { // 비가 1~maxH-1까지 온다
        memset(chk, false, sizeof(chk));
        sink(i);
        int cnt = solve(i);
        ans = max(ans, cnt);
    }
    cout << ans << '\n';
    return 0;
}