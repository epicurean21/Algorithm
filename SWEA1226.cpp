#include <iostream>
#include <queue>
#include <string>
#include <cstring>
using namespace std;
#define MAX 17
int map[MAX][MAX], sx, sy, ex, ey;
int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};
bool chk[MAX][MAX];
string str;

void bfs(int x, int y) {
    queue<pair<int, int>> q;
    q.push({x, y});
    chk[y][x] = true;
    while (!q.empty()) {
        int curx = q.front().first;
        int cury = q.front().second;
        q.pop();

        for (int i = 0; i < 4; i++) {
            int nx = curx + dx[i];
            int ny = cury + dy[i];
            if (nx < 0 || nx >= 16 || ny < 0 || ny >= 16) continue;
            if (map[ny][nx] == 1) continue;
            if (chk[ny][nx]) continue;
            chk[ny][nx] = true;

            q.push({nx, ny});
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    for (int tt = 0; tt < 10; tt++) {
        cin >> t;
        for (int i = 0; i < 16; i++) {
            cin >> str;
            for (int j = 0; j < str.length(); j++) {
                map[i][j] = str[j] - '0';
                if (str[j] == '2') {
                    sx = j;
                    sy = i;
                } else if (str[j] == '3') {
                    ex = j;
                    ey = i;
                }
            }
        }

        memset(chk, false, sizeof(chk));
        bfs(sx, sy);
        if (chk[ey][ex])
            cout << "#" << t << " 1\n";
        else
            cout << "#" << t << " 0\n";
    }
    return 0;
}