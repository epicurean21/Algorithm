#include <iostream>
#include <cstring>
#include <queue>

using namespace std;
#define MAX 101
int N, map[MAX][MAX], ans = INT32_MAX;
int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};
bool chk[MAX][MAX], been[MAX][MAX];

int min(int a, int b) {
    return a > b ? b : a;
}

bool isIsland(int x, int y, int fx, int fy) {
    queue<pair<int, int>> q;
    q.push({x, y});
    memset(been, false, sizeof(been));
    while (!q.empty()) {
        int cx = q.front().first;
        int cy = q.front().second;
        q.pop();
        if (cx == fx && cy == fy) return true;

        been[cy][cx] = true;
        for (int i = 0; i < 4; i++) {
            int nx = cx + dx[i];
            int ny = cy + dy[i];
            if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
            if (been[ny][nx]) continue;
            been[ny][nx] = true;

            q.push({nx, ny});
        }
    }

    return false;
}

void dfs(int x, int y, int cnt) {
    chk[y][x] = true;

    if (cnt >= ans) return;

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
        if (chk[ny][nx]) continue;
        if (map[ny][nx]) {
            if (isIsland(x, y, nx, ny)) {
                ans = min(ans, cnt);
                return;
            } else
                continue;
        }

        dfs(nx, ny, cnt + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> map[i][j];

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (map[i][j] == 0) {
                memset(chk, false, sizeof(chk));
                dfs(j, i, 1);
            }
        }
    }

    cout << ans << "\n";

    return 0;
}