/**
 * 14940 쉬운 최단거리
 * 그래프 이론, BFS
 */
#include "iostream"
#include "queue"

using namespace std;
#define MAX 1001
int n, m, ans[MAX][MAX], map[MAX][MAX], dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};
pair<int, int> target;

bool isPossible(int x, int y) {
    if (x < 0 || x >= m || y < 0 || y >= m) return false;
    if (map[y][x] != 1) return false;
    if (ans[y][x] != -1) return false;
    return true;
}

void bfs() {
    queue<pair<int, pair<int, int>>> qu;
    qu.push({1, {target.second, target.first}});
    while (!qu.empty()) {
        int cur_x = qu.front().second.first;
        int cur_y = qu.front().second.second;
        int mov_count = qu.front().first;
        qu.pop();

        for (int i = 0; i < 4; i++) {
            int next_x = cur_x + dx[i];
            int next_y = cur_y + dy[i];
            if (isPossible(next_x, next_y)) {
                qu.push({mov_count + 1, {next_x, next_y}});
                ans[next_y][next_x] = mov_count;
            }
        }
    }
}

void print_ans() {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << (map[i][j] == 0 ? 0 : ans[i][j] == -1 ? -1 : ans[i][j]) << " ";
        }
        cout << '\n';
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> map[i][j];
            ans[i][j] = -1;
            if (map[i][j] == 2) {
                target.first = i;
                target.second = j;
                ans[i][j] = 0;
            }
        }
    }

    bfs();
    print_ans();

    return 0;
}