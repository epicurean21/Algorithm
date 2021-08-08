#include <iostream>
#include <queue>
#include <string>

using namespace std;
#define MAX 1002
int N, M, map[MAX][MAX], dist[MAX][MAX], dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};
bool visited[MAX][MAX];

void bfs(int sx, int sy) {
    queue<pair<pair<int, int>, pair<int, int>>> q; // x, y, wall, dist
    q.push({{sx, sy},
            {0,  1}});
    visited[sy][sx] = true;
    dist[sy][sx] = 1;
    while (!q.empty()) {
        int cx = q.front().first.first;
        int cy = q.front().first.second;
        int wall_destroy_count = q.front().second.first;
        int distance = q.front().second.second;
        q.pop();

        for (int i = 0; i < 4; i++) {
            int nx = cx + dx[i];
            int ny = cy + dy[i];
            if (nx <= 0 || nx > M || ny <= 0 || ny > N) continue;
            if (map[ny][nx] == 1 && wall_destroy_count >= 1) continue;
            if (visited[ny][nx]) continue;
            visited[ny][nx] = true;
            if (map[ny][nx] == 1)
                wall_destroy_count++;
            dist[ny][nx] = distance + 1;
            q.push({{nx,                 ny},
                    {wall_destroy_count, distance + 1}});
        }
    }
}

void print_dist() {
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++)
            cout << dist[i][j] << " ";
        cout << '\n';
    }
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

    bfs(1, 1);
    if (dist[N][M] == 0)
        cout << "-1\n";
    else
        cout << dist[N][M] << '\n';

    return 0;
}