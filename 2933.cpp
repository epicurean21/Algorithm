#include <iostream>
#include <string>
#include <queue>
#include <cstring>

using namespace std;
#define MAX 102
int Y, X, N, shoot[MAX], h;
char map[MAX][MAX], ans[MAX][MAX];
bool been[MAX][MAX];
int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};
priority_queue<pair<int, int>> pq; // max-heap

void dfs(int x, int y, bool move, int height) {
    been[y][x] = true;
    if (y < Y && move) {
        ans[y][x] = '.';
        ans[y + height][x] = 'x';
    }
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx < 1 || nx > X || ny < 1 || ny > Y) continue;
        if (been[ny][nx]) continue;
        if (map[ny][nx] == '.') continue;
        been[ny][nx] = true;
        dfs(nx, ny, move, height);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> Y >> X;
    for (int i = 1; i <= Y; i++) {
        string str;
        cin >> str;
        for (int j = 1; j <= X; j++) {
            map[i][j] = str[j - 1];
            if (map[i][j] == 'x')
                pq.push({i, j});
        }
    }

    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> h;
        shoot[i] = Y - h + 1;
    }

    for (int i = 0; i < N; i++) {
        int shooting = shoot[i];
        if (i % 2 == 0) { // 왼쪽
            for (int j = 1; j <= X; j++)
                if (map[shooting][j] == 'x') {
                    map[shooting][j] = '.';
                    break;
                }
        } else { // 오른쪽
            for (int j = X; j >= 1; j--)
                if (map[shooting][j] == 'x') {
                    map[shooting][j] = '.';
                    break;
                }
        }
    }
    memcpy(ans, map, sizeof(map));
    while (!pq.empty()) {
        int x = pq.top().second;
        int y = pq.top().first;
        pq.pop();
        if (map[y][x] == '.') continue;
        if (been[y][x]) continue;
        if (y < Y)
            dfs(x, y, true, Y - y);
        else
            dfs(x, y, false, 0);
    }
    for (int i = 1; i <= Y; i++) {
        for (int j = 1; j <= X; j++) {
            cout << ans[i][j];
        }
        cout << '\n';
    }
    return 0;
}