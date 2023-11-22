/**
 * 11060 점프점프
 * 그래프 이론, BFS
 */
#include "iostream"
#include "queue"

using namespace std;
#define MAX 1001
int n, a[MAX], move_count[MAX];

bool isOut(int x) {
    return x < 0 || x >= n;
}

void bfs() {
    queue<pair<int, int>> qu;
    qu.push({0, 0});
    while (!qu.empty()) {
        auto cur = qu.front();
        qu.pop();

        for (int i = cur.first + 1; i <= cur.first + a[cur.first]; i++) {
            int next_i = i;
            if (!isOut(next_i) && move_count[next_i] == 0) {
                move_count[next_i] = cur.second + 1;
                qu.push({next_i, cur.second + 1});
            }
        }
        for (int i = cur.first - 1; i >= cur.first - a[cur.first]; i--) {
            int next_i = i;
            if (!isOut(next_i) && move_count[next_i] == 0) {
                move_count[next_i] = cur.second + 1;
                qu.push({next_i, cur.second + 1});
            }
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];

    bfs();
    cout << (n == 1 ? 0 : move_count[n - 1] == 0 ? -1 : move_count[n - 1]) << '\n';
    return 0;
}