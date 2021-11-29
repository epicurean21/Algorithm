/**
 * 11967 불켜기
 * BFS, 시뮬레이션, 그래프 탐색
 */

#include <iostream>
#include <cstring>
#include <queue>

using namespace std;
#define MAX 101
int N, M, x, y, a, b;
vector<vector<vector<pair<int, int>>>> map;
int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};
int chk[MAX][MAX];

void init() {
    map.resize(N + 1);
    for (int i = 0; i <= N; i++)
        map[i].resize(N + 1);
}

int bfs() {
    int ans = 1;
    queue<pair<int, int>> q;
    q.push({1, 1});
    chk[1][1] = 1;

    while (!q.empty()) {
        auto f = q.front();
        q.pop();
        int cy = f.second, cx = f.first;
        for (auto p : map[cy][cx]) {
            int ny = p.second, nx = p.first;
            if (!chk[ny][nx]) {
                for (int i = 0; i < 4; i++) {
                    int ty = ny + dy[i];
                    int tx = nx + dx[i];
                    if (chk[ty][tx] == 2) {
                        q.push({tx, ty});
                        break;
                    }
                }
                chk[ny][nx] = 1;
                ans++;
            }
        }
        for (int i = 0; i < 4; i++) {
            int ny = cy + dy[i];
            int nx = cx + dx[i];
            if (chk[ny][nx] == 1) {
                chk[ny][nx] = 2;
                q.push({nx, ny});
            }
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N >> M;
    init();
    for (int i = 0; i < M; i++) {
        cin >> x >> y >> a >> b;
        map[y][x].emplace_back(a, b);
    }

    cout << bfs() << '\n';
    return 0;
}