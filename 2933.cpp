#include <iostream>
#include <string>
#include <queue>

using namespace std;
#define MAX 102
int Y, X, N, shoot[MAX], h;
char map[MAX][MAX];
bool been[MAX][MAX];
int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};
priority_queue<pair<int, int>> pq; // min-heap

void dfs(int x, int y, bool move) {
    been[y][x] == true;
    if (y > 1 && move) {
        if (map[y - 1][x] == '.') {
            map[y][x] == '.';
            map[y - 1][x] == 'x';
        }
    }
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx < 1 || nx > X || ny < 1 || ny > Y) continue;
        if (been[ny][nx]) continue;
        dfs(ny, nx, move);
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


    for (int i = 1; i <= Y; i++) {
        for (int j = 1; j <= X; j++) {
            cout << map[i][j];
        }
        cout << '\n';
    }

    while (!pq.empty()) {
        int x = pq.top().second;
        int y = pq.top().first;
        pq.pop();
        if (map[y][x] == '.') continue;
        if (been[y][x]) continue;
        if (y > 1)
            dfs(y, x, true);
        else
            dfs(y, x, false);
    }
    for (int i = 1; i <= Y; i++) {
        for (int j = 1; j <= X; j++) {
            cout << map[i][j];
        }
        cout << '\n';
    }
    return 0;
}