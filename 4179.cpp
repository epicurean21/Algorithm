#include <iostream>
#include <queue>
#include <string>

using namespace std;

#define MAX 1001

int sx, sy;
int T, W, H;
int map[MAX][MAX];
bool visit[MAX][MAX];
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
queue<pair<int, int>> Fire;

int BFS(int x, int y) {
    queue<pair<int, int>> que;
    que.push({x, y});

    int result = 0;
    while (1) {
        result++;
        int fire_size = Fire.size();
        while (fire_size--) {
            int fire_x = Fire.front().first;
            int fire_y = Fire.front().second;
            Fire.pop();

            for (int i = 0; i < 4; i++) {
                int nx = fire_x + dx[i];
                int ny = fire_y + dy[i];

                if (nx < 0 || nx >= H || ny < 0 || ny >= W) continue;
                if (map[nx][ny] == 1) continue;
                map[nx][ny] = 1;
                Fire.push({nx, ny});
            }
        }

        int people_size = que.size();
        if (people_size == 0) return -1;
        while (people_size--) {
            int curx = que.front().first;
            int cury = que.front().second;
            que.pop();

            for (int i = 0; i < 4; i++) {
                int nx = curx + dx[i];
                int ny = cury + dy[i];

                if (nx < 0 || nx >= H || ny < 0 || ny >= W) return result;
                if (visit[nx][ny] || map[nx][ny] == 1) continue;
                map[nx][ny] = 2;
                visit[nx][ny] = true;
                que.push(make_pair(nx, ny));
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
        cin >> H >> W;

    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            char temp;
            cin >> temp;
            if (temp == '#') map[i][j] = 1;
            else if (temp == 'F') {
                map[i][j] = 1;
                Fire.push({i, j});
            } else if (temp == 'J') {
                sx = i;
                sy = j;
                map[i][j] = 2;
            } else
                map[i][j] = 0;
        }
    }

    int check = BFS(sx, sy);
    if (check == -1) cout << "IMPOSSIBLE" << "\n";
    else cout << check << "\n";

    return 0;
}