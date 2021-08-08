#include <iostream>
#include <queue>
#include <string>

using namespace std;
#define MAX 1002
int N, M, map[MAX][MAX], dist[2][MAX][MAX], dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};
bool visited[2][MAX][MAX];

void bfs(int sx, int sy) {
    queue<pair < pair < int, int>, pair < int, int>>> q; // x, y, wall, dist
    q.push({{sx, sy},
            {0,  1}});
    visited[0][sy][sx] = true;
    dist[0][sy][sx] = 1;
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
            if (visited[wall_destroy_count][ny][nx]) continue;
            visited[wall_destroy_count][ny][nx] = true;
            bool wall_found = false;
            if (map[ny][nx] == 1) {
                wall_found = true;
                dist[1][ny][nx] = distance + 1;
            } else {
                dist[wall_destroy_count][ny][nx] = distance + 1;
            }
            if (wall_found)
                q.push({{nx, ny},
                        {1,  distance + 1}});
            else
                q.push({{nx, ny},
                        {0,  distance + 1}});
        }
    }
}

void print_dist() {
    for (int d = 0; d < 2; d++) {
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= M; j++)
                cout << dist[d][i][j] << " ";
            cout << '\n';
        }
        cout << "---------\n";
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
    print_dist();
    if (dist[0][N][M] == 0 && dist[1][N][M] == 0)
        cout << "-1\n";
    else {
        if (dist[0][N][M] == 0)
            cout << dist[1][N][M] << "\n";
        else
            cout << dist[0][N][M] << "\n";
    }

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