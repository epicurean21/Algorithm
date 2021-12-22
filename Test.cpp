/**
 * 17144 미세먼지 안녕!
 * 구현, 시뮬레이션
 */
#include <iostream>
#include <cstring>

using namespace std;
#define MAX 51

int R, C, T, map[MAX][MAX], tmp[MAX][MAX], dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};
pair<pair<int, int>, int> air_cleaner;

int count_map() {
    int cnt = 0;
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            if (map[i][j] > 0)
                cnt += map[i][j];

    return cnt;
}

void spread() {
    for (int y = 0; y < R; y++) {
        for (int x = 0; x < C; x++) {
            if (map[y][x] > 0) { // 미세먼지
                int cnt = 0;
                int pol = map[y][x];
                for (int k = 0; k < 4; k++) {
                    int nx = x + dx[k];
                    int ny = y + dy[k];
                    if (nx < 0 || ny < 0 || nx >= C || ny >= R) continue;
                    if (map[ny][nx] == -1) continue;
                    cnt++;
                    tmp[ny][nx] += (pol / 5);
                }
                tmp[y][x] += pol - ((pol / 5) * cnt);
            }
        }
    }
    memcpy(map, tmp, sizeof(map));
    memset(tmp, 0, sizeof(tmp));
}

void active_air_cleaner() {
    int down = air_cleaner.first.first;
    int up = air_cleaner.first.second;

    for (int u = 0; u < 2; u++) {
        if (u == 0) {
            for (int i = up - 1; i > 0; i--)
                map[i][0] = map[i - 1][0];
            for (int i = 0; i < C - 1; i++)
                map[0][i] = map[0][i + 1];
            for (int i = 1; i <= up; i++)
                map[i - 1][C - 1] = map[i][C - 1];
            for (int i = C - 1; i > 1; i--)
                map[up][i] = map[up][i - 1];
            map[up][1] = 0;
        } else {
            for (int i = down + 1; i < R - 1; i++)
                map[i][0] = map[i + 1][0];
            for (int i = 0; i < C - 1; i++)
                map[R - 1][i] = map[R - 1][i + 1];
            for (int i = R - 1; i >= down; i--)
                map[i][C - 1] = map[i - 1][C - 1];
            for (int i = C - 1; i > 1; i--)
                map[down][i] = map[down][i - 1];

            map[down][1] = 0;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> R >> C >> T;
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++) {
            cin >> map[i][j];
            if (map[i][j] == -1) {
                air_cleaner.second = j;
                if (air_cleaner.first.first == 0)
                    air_cleaner.first.first = i;
                else
                    air_cleaner.first.second = i;
            }
        }

    while (T--) {
        spread();
        active_air_cleaner();
    }
    cout << count_map() << "\n";
    return 0;
}