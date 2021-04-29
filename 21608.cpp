#include <iostream>
#include <cmath>
#include <queue>
#include <algorithm>

using namespace std;
#define MAX 402
int N, s, favorite[MAX][5], map[21][21], ans;
int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};
queue<int> student;

int calculate_score(int cnt) {
    if (cnt == 0) return 0;
    return pow(10, cnt - 1);
}

pair<int, int> count_empty(int cur, int x, int y) {
    int tmp_empty = 0, tmp_cnt = 0;
    for (int k = 0; k < 4; k++) {
        int nx = x + dx[k];
        int ny = y + dy[k];
        if (nx <= 0 || nx > N || ny <= 0 || ny > N) continue;
        int next = map[ny][nx];
        if (!next) tmp_empty++;
        for (int f = 0; f < 4; f++) {
            if (favorite[cur][f] == next)
                tmp_cnt++;
        }
    }
    return {tmp_cnt, tmp_empty};
}

void solve() {
    while (!student.empty()) {
        int cur = student.front();
        student.pop();
        int fav_cnt = -1, empty_cnt = -1, x = N + 1, y = N + 1;
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                if (map[i][j]) continue;
                pair<int, int> tmp = count_empty(cur, j, i);

                if (fav_cnt <= tmp.first) { // 1번
                    if (fav_cnt == tmp.first) {
                        if (empty_cnt <= tmp.second) { // 2번
                            if (empty_cnt == tmp.second) {
                                if (y >= i) { // 3번
                                    if (y == i) { // 행이 같다
                                        if (x > j) { // 열이 작다
                                            x = j;
                                            y = i;
                                            fav_cnt = tmp.first;
                                            empty_cnt = tmp.second;
                                        }
                                    } else { // 행이 더 작음
                                        x = j;
                                        y = i;
                                        fav_cnt = tmp.first;
                                        empty_cnt = tmp.second;
                                    }
                                }
                            } else {
                                x = j;
                                y = i;
                                fav_cnt = tmp.first;
                                empty_cnt = tmp.second;
                            }
                        }
                    } else {
                        x = j;
                        y = i;
                        fav_cnt = tmp.first;
                        empty_cnt = tmp.second;
                    }
                }
            }
        }
        map[y][x] = cur;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    for (int i = 1; i <= N * N; i++) {
        cin >> s;
        student.push(s);
        for (int j = 0; j < 4; j++)
            cin >> favorite[s][j];
    }
    solve();
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            pair<int, int> cnt = count_empty(map[i][j], j, i);
            ans += calculate_score(cnt.first);
        }
    }
    cout << ans;
    return 0;
}