#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>

using namespace std;
#define MAX 51
#define INF 9999999

char map[MAX][MAX];
int n;
int height[MAX][MAX];
int range[2600];
int visit[MAX][MAX];
int sol = INF;
int dx[] = {0, -1, 1, 0, -1, 1, -1, 1};
int dy[] = {-1, 0, 0, 1, -1, -1, 1, 1};

int dfs(int y, int x, int s, int e) {
    int cur = 0;
    if (height[y][x] < s || height[y][x] > e)
        return 0;
    if (map[y][x] == 'K')
        cur = 1;

    for (int i = 0; i < 8; i++) {
        int ny = y + dy[i];
        int nx = x + dx[i];

        if (nx >= 0 && nx < n && ny >= 0 && ny < n) {
            if (visit[ny][nx] == 0) {
                visit[ny][nx] = 1;
                cur += dfs(ny, nx, s, e);
            }
        }
    }
    return cur;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    string str;
    for (int i = 0; i < n; i++) {
        cin >> str;
        for (int j = 0; j < str.size(); j++)
            map[i][j] = str[j];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> height[i][j];
            range[i * n + j] = height[i][j];
        }
    }

    int sz = 0;
    int starty, startx;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (map[i][j] == 'P') {
                starty = i;
                startx = j;
            }
            if (map[i][j] == 'K')
                sz++;
        }
    }
    sort(range, range + n * n);

    int cnt = 1;
    for (int i = 1; i < n * n; i++) {
        if (range[i - 1] != range[i])
            range[cnt++] = range[i];
    }

    int s = 0, e = 0;
    while (e < cnt) {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                visit[i][j] = 0;

        visit[starty][startx] = 1;
        if (dfs(starty, startx, range[s], range[e]) == sz) {
            if (range[e] - range[s] < sol)
                sol = range[e] - range[s];
            s++;
        } else
            e++;
    }

    cout << sol << '\n';
    return 0;
}