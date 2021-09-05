/**
 * 1926: 그림
 * DFS, BFS로 풀면된다
 * 총 그림의 개수, 그중 가장 넓은 그림의 크기 구하면 댐 좆밥임
 */
#include <iostream>
#include <vector>
#include <queue>

using namespace std;
#define MAX 502
int n, m, cnt, max_size, map[MAX][MAX], dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};
bool chk[MAX][MAX];

int bfs(int x, int y) {
    int res = 0;
    queue<pair<int, int>> q;
    q.push({x, y});

    while (!q.empty()) {
        int cx = q.front().first;
        int cy = q.front().second;
        q.pop();

        chk[cy][cx] = true;
        res++;
        for (int i = 0; i < 4; i++) {
            int nx = cx + dx[i];
            int ny = cy + dy[i];

            if (nx < 0 || nx >= m || ny < 0 || ny >= n) continue;
            if (!map[ny][nx]) continue;
            if (!chk[ny][nx]) {
                chk[ny][nx] = true;
                q.push({nx, ny});
            }
        }
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> map[i][j];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (map[i][j] == 1 && !chk[i][j]) {
                cnt++;
                max_size = max(bfs(j, i), max_size);
            }
        }
    }

    cout << cnt << '\n' << max_size << '\n';
    return 0;
}