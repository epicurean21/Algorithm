#include <iostream>
#include <string>
#include <cstring>

using namespace std;
#define MAX 101
int N, dy[] = {0, 1, 0, -1}, dx[] = {1, 0, -1, 0};
char map[MAX][MAX];
bool chk[MAX][MAX];
int cnt1, cnt2;

void dfs(int x, int y, char color) {
    chk[y][x] = true;
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
        if (map[ny][nx] != color) continue;
        if (!chk[ny][nx]) {
            dfs(nx, ny, color);
        }
    }
}

void dfs2(int x, int y, char color) {
    chk[y][x] = true;
    if (color == 'R' || color == 'G') {
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
            if (map[ny][nx] == 'B') continue;
            if (!chk[ny][nx])
                dfs2(nx, ny, color);
        }
    } else {
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
            if (map[ny][nx] != color) continue;
            if (!chk[ny][nx])
                dfs2(nx, ny, color);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    for (int i = 0; i < N; i++) {
        string str;
        cin >> str;
        for (int j = 0; j < str.length(); j++)
            map[i][j] = str[j];
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (!chk[i][j]) {
                cnt1++;
                dfs(j, i, map[i][j]);
            }
        }
    }
    memset(chk, false, sizeof(chk));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (!chk[i][j]) {
                cnt2++;
                dfs2(j, i, map[i][j]);
            }
        }
    }
    cout << cnt1 << " " << cnt2 << '\n';
    return 0;
}