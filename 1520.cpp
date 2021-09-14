/**
 * 1520: 내리막 길
 * 그래프 탐색, DP, DFS
 * 걍 4방향 탐색하면 시간초과임
 * dp[i][j] = (i, j)는 N-1, M-1까지 dp[i][j]개 경로 저장
 * 근데 dp값이 0일 수 있음 그래서 -1로 초기화해줘야함;; 이거 질문검색서 알게댐 ...
 */
#include <iostream>
#include <cstring>

using namespace std;
#define MAX 502
int N, M, map[MAX][MAX], dp[MAX][MAX], dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};

int dfs(int x, int y) {
    if (y == M - 1 && x == N - 1)
        return 1;
    if (dp[y][x] != -1)
        return dp[y][x];
    dp[y][x] = 0;

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
        if (map[ny][nx] < map[y][x])
            dp[y][x] += dfs(nx, ny);
    }

    return dp[y][x];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> M >> N;
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            cin >> map[i][j];

    memset(dp, -1, sizeof(dp));
    cout << dfs(0, 0) << '\n';

    return 0;
}