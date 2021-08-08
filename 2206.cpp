#include <iostream>
#include <queue>
#include <string>

using namespace std;
#define MAX 1002
int N, M, map[MAX][MAX], dist[2][MAX][MAX], dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};

int bfs(int sx, int sy) {
    queue<pair<pair<int, int>, int>> q; // x, y, wall
    q.push({{1, 1}, 0});
    dist[0][sy][sx] = 1;

    while (!q.empty()) {
        int cx = q.front().first.first;
        int cy = q.front().first.second;
        int wall_destroy_count = q.front().second;
        q.pop();

        if (cy == N && cx == M)
            return dist[wall_destroy_count][cy][cx];

        for (int i = 0; i < 4; i++) {
            int nx = cx + dx[i];
            int ny = cy + dy[i];
            if (nx <= 0 || nx > M || ny <= 0 || ny > N) continue;
            if (dist[wall_destroy_count][ny][nx]) continue;

            if (map[ny][nx] == 0) {
                dist[wall_destroy_count][ny][nx] = dist[wall_destroy_count][cy][cx] + 1;
                q.push({{nx, ny}, wall_destroy_count});
            } else if (map[ny][nx] == 1 && wall_destroy_count == 0) {
                dist[1][ny][nx] = dist[wall_destroy_count][cy][cx] + 1;
                q.push({{nx, ny}, 1});
            }
        }
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N >> M;

    for (int i = 1; i <= N; i++) {
        string str;
        cin >> str;
        for (int j = 0; j < str.length(); j++)
            map[i][j + 1] = str[j] - '0';
    }

    cout << bfs(1, 1) << '\n';

    return 0;
}

/**
8 8
01000100
01010100
01010100
01010100
01010100
01010100
01010100
00010100
 */