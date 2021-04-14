#include <iostream>
#include <vector>
#include <cstring>

using namespace std;
#define MAX 10
#define INF 100
int N, M, map[MAX][MAX], ans = INF;
int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};
vector<pair<int, int>> camera;

int min(int a, int b) {
    return a > b ? b : a;
}

int countMap() {
    int cnt = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            if (map[i][j] == 0)
                cnt++;
    return cnt;
}

void printMap() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++)
            cout << map[i][j] << " ";
        cout << '\n';
    }
}

bool over(int x, int y) {
    if (x < 0 || x >= M || y < 0 || y >= N)
        return true;
    else
        return false;
}

void solve(int x, int y, int num) {
    int dir = map[y][x];
    int tmpMap[MAX][MAX];
    memcpy(tmpMap, map, sizeof(tmpMap));
    switch (dir) {
        case 1:
            for (int i = 0; i < 4; i++) {
                int cx = x, cy = y;
                memcpy(map, tmpMap, sizeof(map));
                while (1) {
                    if (over(cx + dx[i], cy + dy[i])) break;
                    if (map[cy + dy[i]][cx + dx[i]] == 6) break;
                    if (map[cy + dy[i]][cx + dx[i]] == 0) {
                        map[cy + dy[i]][cx + dx[i]] = -1;
                        cy += dy[i];
                        cx += dx[i];
                    } else {
                        cy += dy[i];
                        cx += dx[i];
                    }
                }

                if (num == camera.size() - 1) {
                    ans = min(ans, countMap());
                } else {
                    int nx = camera[num + 1].first;
                    int ny = camera[num + 1].second;
                    solve(nx, ny, num + 1);
                }
            }
            break;

        case 2:
            for (int i = 0; i < 2; i++) {
                int cx = x, cy = y;
                memcpy(map, tmpMap, sizeof(map));
                if (i == 1) { // <- ->
                    for (int j = cx - 1; j >= 0; j--) { // 왼
                        if (map[cy][j] == 6) break;
                        if (map[cy][j] == 0)
                            map[cy][j] = -1;
                    }
                    for (int j = cx + 1; j < M; j++) { // 우
                        if (map[cy][j] == 6) break;
                        if (map[cy][j] == 0)
                            map[cy][j] = -1;
                    }
                } else {
                    for (int j = cy - 1; j >= 0; j--) { // 위
                        if (map[j][cx] == 6) break;
                        if (map[j][cx] == 0)
                            map[j][cx] = -1;
                    }
                    for (int j = cy + 1; j < N; j++) { // 아래
                        if (map[j][cx] == 6) break;
                        if (map[j][cx] == 0)
                            map[j][cx] = -1;
                    }
                }

                if (num == camera.size() - 1) {
                    ans = min(ans, countMap());
                } else {
                    int nx = camera[num + 1].first;
                    int ny = camera[num + 1].second;
                    solve(nx, ny, num + 1);
                }
            }
            break;

        case 3:
            for (int i = 0; i < 4; i++) {
                int cx = x, cy = y;
                memcpy(map, tmpMap, sizeof(map));
                if (i == 0) { // 왼 위
                    for (int j = cx - 1; j >= 0; j--) {
                        if (map[cy][j] == 6) break;
                        if (map[cy][j] == 0)
                            map[cy][j] = -1;
                    }
                    for (int j = cy - 1; j >= 0; j--) {
                        if (map[j][cx] == 6) break;
                        if (map[j][cx] == 0)
                            map[j][cx] = -1;
                    }
                } else if (i == 1) { // 우 아래
                    for (int j = cx + 1; j < M; j++) {
                        if (map[cy][j] == 6) break;
                        if (map[cy][j] == 0)
                            map[cy][j] = -1;
                    }
                    for (int j = cy + 1; j < N; j++) {
                        if (map[j][cx] == 6) break;
                        if (map[j][cx] == 0)
                            map[j][cx] = -1;
                    }
                } else if (i == 2) { // 우 위
                    for (int j = cx + 1; j < M; j++) {
                        if (map[cy][j] == 6) break;
                        if (map[cy][j] == 0)
                            map[cy][j] = -1;
                    }
                    for (int j = cy - 1; j >= 0; j--) {
                        if (map[j][cx] == 6) break;
                        if (map[j][cx] == 0)
                            map[j][cx] = -1;
                    }
                } else { // 왼 아래
                    for (int j = cx - 1; j >= 0; j--) {
                        if (map[cy][j] == 6) break;
                        if (map[cy][j] == 0)
                            map[cy][j] = -1;
                    }
                    for (int j = cy + 1; j < N; j++) {
                        if (map[j][cx] == 6) break;
                        if (map[j][cx] == 0)
                            map[j][cx] = -1;
                    }
                }

                if (num == camera.size() - 1) {
                    ans = min(ans, countMap());
                } else {
                    int nx = camera[num + 1].first;
                    int ny = camera[num + 1].second;
                    solve(nx, ny, num + 1);
                }
            }
            break;

        case 4:
            for (int i = 0; i < 4; i++) {
                int cx = x, cy = y;
                memcpy(map, tmpMap, sizeof(map));

                if (i == 0) { // 왼 우 위
                    for (int j = cx - 1; j >= 0; j--) { // 왼
                        if (map[cy][j] == 6) break;
                        if (map[cy][j] == 0)
                            map[cy][j] = -1;
                    }
                    for (int j = cx + 1; j < M; j++) { // 우
                        if (map[cy][j] == 6) break;
                        if (map[cy][j] == 0)
                            map[cy][j] = -1;
                    }
                    for (int j = cy - 1; j >= 0; j--) { // 위
                        if (map[j][cx] == 6) break;
                        if (map[j][cx] == 0)
                            map[j][cx] = -1;
                    }
                } else if (i == 1) { // 왼 우 아래
                    for (int j = cx - 1; j >= 0; j--) { // 왼
                        if (map[cy][j] == 6) break;
                        if (map[cy][j] == 0)
                            map[cy][j] = -1;
                    }
                    for (int j = cx + 1; j < M; j++) { // 우
                        if (map[cy][j] == 6) break;
                        if (map[cy][j] == 0)
                            map[cy][j] = -1;
                    }
                    for (int j = cy + 1; j < N; j++) { // 아래
                        if (map[j][cx] == 6) break;
                        if (map[j][cx] == 0)
                            map[j][cx] = -1;
                    }
                } else if (i == 2) { // 위 아래 왼
                    for (int j = cy - 1; j >= 0; j--) { // 위
                        if (map[j][cx] == 6) break;
                        if (map[j][cx] == 0)
                            map[j][cx] = -1;
                    }
                    for (int j = cy + 1; j < N; j++) { // 아래
                        if (map[j][cx] == 6) break;
                        if (map[j][cx] == 0)
                            map[j][cx] = -1;
                    }
                    for (int j = cx - 1; j >= 0; j--) { // 왼
                        if (map[cy][j] == 6) break;
                        if (map[cy][j] == 0)
                            map[cy][j] = -1;
                    }
                } else { // 위 아래 우
                    for (int j = cy - 1; j >= 0; j--) { // 위
                        if (map[j][cx] == 6) break;
                        if (map[j][cx] == 0)
                            map[j][cx] = -1;
                    }
                    for (int j = cy + 1; j < N; j++) { // 아래
                        if (map[j][cx] == 6) break;
                        if (map[j][cx] == 0)
                            map[j][cx] = -1;
                    }
                    for (int j = cx + 1; j < M; j++) { // 우
                        if (map[cy][j] == 6) break;
                        if (map[cy][j] == 0)
                            map[cy][j] = -1;
                    }
                }
                if (num == camera.size() - 1) {
                    ans = min(ans, countMap());
                } else {
                    int nx = camera[num + 1].first;
                    int ny = camera[num + 1].second;
                    solve(nx, ny, num + 1);
                }
            }
            break;

        case 5:
            int cx = x, cy = y;
            memcpy(map, tmpMap, sizeof(map));

            for (int j = cx - 1; j >= 0; j--) { // 왼
                if (map[cy][j] == 6) break;
                if (map[cy][j] == 0)
                    map[cy][j] = -1;
            }
            for (int j = cx + 1; j < M; j++) { // 우
                if (map[cy][j] == 6) break;
                if (map[cy][j] == 0)
                    map[cy][j] = -1;
            }

            // 위
            for (int j = cy - 1; j >= 0; j--) {
                if (map[j][cx] == 6) break;
                if (map[j][cx] == 0)
                    map[j][cx] = -1;
            }
            // 아래
            for (int j = cy + 1; j < N; j++) {
                if (map[j][cx] == 6) break;
                if (map[j][cx] == 0)
                    map[j][cx] = -1;
            }

            if (num == camera.size() - 1) {
                ans = min(ans, countMap());
            } else {
                int nx = camera[num + 1].first;
                int ny = camera[num + 1].second;
                solve(nx, ny, num + 1);
            }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> map[i][j];
            if (map[i][j] < 6 && map[i][j] >= 1) {
                camera.push_back({j, i}); // x, y
            }
        }
    }

    if (camera.size() < 1) {
        ans = countMap();
        cout << ans << '\n';
    } else {
        solve(camera[0].first, camera[0].second, 0);
        cout << ans << '\n';
    }
    return 0;
}

/*
5 2
0 0
0 0
3 0
0 0
6 0

6 6
0 0 0 0 0 5
2 2 2 2 2 2
0 0 0 0 6 5
0 6 2 2 2 5
0 0 0 0 0 5
5 5 5 5 5 5

 */