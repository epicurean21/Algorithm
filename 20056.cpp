/**
 * 20056: 마법사 상어와 파이어볼
 * 삼성 S/W 검정 시험
 */

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;
#define MAX 52
int N, M, K, r, c, m, d, s, ans;
int map[MAX][MAX];
queue<pair<pair<int, int>, pair<pair<int, int>, int>>> fireballs; // x, y, 질량, 방향, 속력
vector<pair<pair<int, int>, int>> overlap[MAX][MAX];

int dx[] = {0, 1, 1, 1, 0, -1, -1, -1}, dy[] = {1, 1, 0, -1, -1, -1, 0, 1};

void init() {
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            overlap[i][j].clear();
}

void spell_active(int cnt) {
    while (cnt--) {
        int x = fireballs.front().first.first;
        int y = fireballs.front().first.second;
        int mass = fireballs.front().second.first.first;
        int dir = fireballs.front().second.first.second;
        int speed = fireballs.front().second.second;
        fireballs.pop();

        map[y][x] -= 1;
        int nx = x + dx[dir] * speed;
        if (nx < 1) nx = N - (abs(nx) % N);
        else nx = nx % N;
        int ny = y + dy[dir] * speed;
        if (ny < 1) ny = N - (abs(ny) % N);
        else ny = ny % N;
        cout << "nx: " << nx << ", ny: " << ny << '\n';

        map[ny][nx] += 1;
        overlap[ny][nx].push_back({{mass, dir},
                                   speed});

        fireballs.push({{nx,          ny},
                        {{mass, dir}, speed}});
    }
}

void magic() {
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (map[i][j] >= 2) {
                int cnt = 0;
                int mass = 0;
                int speed = 0;
                int dir = -1;
                int final_dir = -1;
                for (int k = 0; k < overlap[i][j].size(); k++) {
                    cnt++;
                    mass += overlap[i][j][k].first.first;
                    speed += overlap[i][j][k].second;
                    if (dir == -1) dir = overlap[i][j][k].first.second;
                    else {
                        if (final_dir != -1) continue;
                        if ((dir % 2 == 0 && overlap[i][j][k].first.second % 2 == 0)
                            || (dir % 2 == 1 && overlap[i][j][k].first.second % 2 == 1))
                            final_dir = 0;
                        else
                            final_dir = 1;
                    }
                }

                int new_mass = mass / 5;
                int new_speed = speed / cnt;
                if (new_mass == 0) continue;

                if (final_dir) {
                    for (int k = 1; k < 8; k += 2) {
                        int y = i + dy[k];
                        if (y < 1) y = N - (abs(y) % N);
                        else y = y % N;
                        int x = j + dx[k];
                        if (x < 1) x = N - ((abs(x) % N));
                        else x = x % N;
                        fireballs.push({{x,             y},
                                        {{new_mass, k}, new_speed}});
                    }
                } else {
                    for (int k = 0; k < 8; k += 2) {
                        int y = i + dy[k];
                        if (y < 1) y = N - (abs(y) % N);
                        else y = y % N;
                        int x = j + dx[k];
                        if (x < 1) x = N - ((abs(x) % N));
                        else x = x % N;
                        fireballs.push({{x,             y},
                                        {{new_mass, k}, new_speed}});
                    }
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N >> M >> K;

    for (int i = 0; i < M; i++) {
        cin >> r >> c >> m >> d >> s;
        fireballs.push({{c,      r},
                        {{m, d}, s}});
        map[r][c] += 1;
    }

    while (K-- && !fireballs.empty()) {
        init();
        spell_active(fireballs.size());
        magic();
    }

    while (!fireballs.empty()) {
        ans += fireballs.front().second.first.first;
        fireballs.pop();
    }

    cout << ans << '\n';

    return 0;
}