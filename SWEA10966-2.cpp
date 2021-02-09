#include <iostream>
#include <queue>
#include <string>

using namespace std;
#define MAX 1001
int T, N, M, map[MAX][MAX], ans;
int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};
queue<pair<int, int>> q;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> T;
    for (int t = 1; t <= T; t++) {
        ans = 0;
        cin >> N >> M;
        for (int i = 0; i < N; i++) {
            string str;
            cin >> str;
            for (int j = 0; j < M; j++) {
                if (str[j] == 'W') {
                    map[i][j] = 0;
                    q.push({j, i});
                } else if (str[j] == 'L') {
                    map[i][j] = -1;
                }
            }
        }
        while (!q.empty()) {
            int curx = q.front().first;
            int cury = q.front().second;
            q.pop();
            for (int i = 0; i < 4; i++) {
                int nx = curx + dx[i];
                int ny = cury + dy[i];
                if (nx < 0 || nx >= M || ny < 0 || ny >= N) continue;
                if (map[ny][nx] == -1) {
                    map[ny][nx] = map[cury][curx] + 1;
                    ans += map[ny][nx];
                    q.push({nx, ny});
                }
            }
        }
        cout << "#" << t << " " << ans << '\n';
    }
    return 0;
}