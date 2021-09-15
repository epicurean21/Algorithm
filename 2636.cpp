/**
 * 2636: 치즈
 * DFS, BFS, Simulation
 */
#include <iostream>
#include <vector>

using namespace std;
#define MAX 101
int N, M, map[MAX][MAX], dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1}, cnt, ans, ans2;
bool chk[MAX][MAX];

void init() {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            chk[i][j] = false;
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
        side_cnt++;
    }

    if (side_cnt) {
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
        ans++;
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                if (map[i][j] && !chk[i][j])
                    dfs(j, i);

        if (cnt) ans2 = cnt;
    }

    cout << ans << '\n' << ans2 << '\n';
    return 0;
}