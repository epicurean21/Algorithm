#include <iostream>
#include <queue>
#include <vector>

#define MAX 21

using namespace std;

int n, a[MAX][MAX], check[MAX][MAX], shark_x, shark_y, eat_cnt, shark_size = 2;
int min_dist, min_x, min_y, result;
int dx[] = {0, 0, 1, -1}, dy[] = {-1, 1, 0, 0};

void init_check() {
    min_dist = INT32_MAX;
    min_x = MAX;
    min_y = MAX;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            check[i][j] = -1;
        }
    }
}

void bfs(int x, int y) {
    queue<pair<int, int>> q;
    check[x][y] = 0;
    q.push({x, y});

    while (!q.empty()) {
        pair<int, int> cur = q.front();
        q.pop();
        int x = cur.first;
        int y = cur.second;

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx < 1 || nx > n || ny < 1 || ny > n) continue;
            if (check[nx][ny] != -1 || a[nx][ny] > shark_size) continue;

            check[nx][ny] = check[x][y] + 1;

            if (a[nx][ny] != 0 && a[nx][ny] < shark_size) {
                if (min_dist > check[nx][ny]) {
                    min_x = nx;
                    min_y = ny;
                    min_dist = check[nx][ny];
                } else if (min_dist == check[nx][ny]) {
                    if (min_x == nx) {
                        if (min_y > ny) {
                            min_x = nx;
                            min_y = ny;
                        }
                    } else if (min_x > nx) {
                        min_x = nx;
                        min_y = ny;
                    }
                }
            }

            q.push({nx, ny});
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cin >> a[i][j];
            if (a[i][j] == 9) {
                shark_x = i;
                shark_y = j;
                a[i][j] = 0;
            }
        }
    }

    while (1) {
        init_check();
        bfs(shark_x, shark_y);

        if (min_x != MAX && min_y != MAX) {
            result += check[min_x][min_y];
            eat_cnt++;

            if (eat_cnt == shark_size) {
                shark_size++;
                eat_cnt = 0;
            }

            a[min_x][min_y] = 0;
            shark_x = min_x;
            shark_y = min_y;
        } else
            break;
    }

    cout << result << '\n';
}