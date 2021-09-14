/**
 * 1520: 내리막 길
 * 그래프 탐색, DP, DFS
 */
#include <iostream>

using namespace std;
#define MAX 502
int N, M, map[MAX][MAX], dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1}, ans;
bool chk[MAX][MAX];

void dfs(int x, int y) {
    chk[y][x] = true;
    if (y == M - 1 && x == N - 1) {
        ans++;
        return;
    }

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
        if (chk[ny][nx]) continue;
        if (map[ny][nx] < map[y][x]) {
            chk[ny][nx] = true;
            dfs(ny, nx);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> M >> N;
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            cin >> map[i][j];

    dfs(0, 0);

    cout << ans << '\n';

    return 0;
}