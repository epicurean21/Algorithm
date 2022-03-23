/**
 * 14466 소가 길을 건너간 이유 6
 * 그래프 이론, 그래프 탐색, BFS
 */
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;
#define MAX 101

int N, K, R, roads[MAX][MAX][4] = {0,}, r, c, rr, cc;
bool visited[MAX][MAX];
int dy[] = {-1, 0, 1, 0}, dx[] = {0, 1, 0, -1};

vector<pair<int, int>> cow;
int ans = 0;

void bfs(int y, int x) {
    queue<pair<int, int >> q;
    q.push(make_pair(y, x));
    visited[y][x] = true;

    while (!q.empty()) {
        int cy = q.front().first;
        int cx = q.front().second;
        q.pop();

        for (int i = 0; i < 4; i++) {
            if (roads[cy][cx][i] == 1) continue;
            int ny = cy + dy[i];
            int nx = cx + dx[i];

            if (ny < 1 || ny > N || nx < 1 || nx > N)continue;
            if (visited[ny][nx]) continue;

            q.push(make_pair(ny, nx));
            visited[ny][nx] = true;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> K >> R;

    for (int i = 0; i < R; i++) {
        cin >> r >> c >> rr >> cc;
        for (int j = 0; j < 4; j++) {
            int nr = r + dy[j];
            int nc = c + dx[j];
            if (nr == rr && nc == cc) {
                roads[r][c][j] = 1;
                roads[rr][cc][(j + 2) % 4] = 1;
            }
        }
    }

    for (int i = 0; i < K; i++) {
        cin >> r >> c;
        cow.emplace_back(r, c);
    }

    for (int i = 0; i < K; i++) {
        memset(visited, 0, sizeof(visited));
        bfs(cow[i].first, cow[i].second);

        for (int j = i + 1; j < K; j++) {
            if (visited[cow[j].first][cow[j].second] == 0)
                ans++;
        }
    }

    cout << ans << '\n';
    return 0;
}