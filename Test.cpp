/**
 * 1600 말이 되고픈 원숭이
 * 구현, 그래프이론, 너비우선탐색
 */
#include "iostream"
#include "queue"
#include "vector"

using namespace std;
#define MAX 201
int K, W, H, map[MAX][MAX], ans[MAX][MAX];
int horse_move_x[] = {2, 1, -1, -2, -2, -1, 1, 2}, horse_move_y[] = {-1, -2, -2, -1, 1, 2, 2, 1};
int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};

bool is_possible(int x, int y) {
    if (x < 0 || x >= W || y < 0 || y >= H) return false;
    if (map[y][x] == 1) return false;
    return true;
}

void solve() {
    queue<pair<pair<int, int>, pair<int, int>>> q; // {move, k remain}, {x, y}
    bool visited[K + 1][MAX][MAX]; // using horse, or not
    q.push({{0, K},
            {0, 0}});

    while (!q.empty()) {
        int cnt = q.front().first.first;
        int remaining_k = q.front().first.second;
        int cur_x = q.front().second.first;
        int cur_y = q.front().second.second;
        q.pop();

        if (ans[cur_y][cur_x] > cnt) ans[cur_y][cur_x] = cnt;

        if (remaining_k) {
            for (int i = 0; i < 8; i++) {
                int nx = cur_x + horse_move_x[i];
                int ny = cur_y + horse_move_y[i];

                if (is_possible(nx, ny)) {
                    if (!visited[remaining_k - 1][ny][nx]) {
                        visited[remaining_k - 1][ny][nx] = true;
                        q.push({{cnt + 1, remaining_k - 1},
                                {nx,      ny}});
                    }
                }
            }
        }

        for (int i = 0; i < 4; i++) {
            int nx = cur_x + dx[i];
            int ny = cur_y + dy[i];
            if (is_possible(nx, ny)) {
                if (!visited[remaining_k][ny][nx]) {
                    visited[remaining_k][ny][nx] = true;
                    q.push({{cnt + 1, remaining_k},
                            {nx,      ny}});
                }
            }
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> K >> W >> H;
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            cin >> map[i][j];
            ans[i][j] = INT32_MAX;
        }
    }

    solve();

    if (ans[H - 1][W - 1] == INT32_MAX) cout << "-1\n";
    else cout << ans[H - 1][W - 1] << '\n';

    return 0;
}