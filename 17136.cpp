#include <iostream>

using namespace std;
#define MAX 11
#define INF 987312341
int map[MAX][MAX], cnt, ans = INF;
int paper[] = {0, 5, 5, 5, 5, 5};
int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};

int five[5][5] = {{1, 1, 1, 1, 1},
                  {1, 1, 1, 1, 1},
                  {1, 1, 1, 1, 1},
                  {1, 1, 1, 1, 1},
                  {1, 1, 1, 1, 1}};
int four[4][4] = {{1, 1, 1, 1},
                  {1, 1, 1, 1},
                  {1, 1, 1, 1},
                  {1, 1, 1, 1}};
int three[3][3] = {{1, 1, 1},
                   {1, 1, 1},
                   {1, 1, 1}};
int two[2][2] = {{1, 1},
                 {1, 1}};
int one[1] = {1};

void dfs(int x, int y) {
    if (x == 10) {
        dfs(0, y + 1);
        return;
    }
    if (y == 10) {
        ans = min(ans, cnt);
        return;
    }

    if (map[y][x] == 0) {
        dfs(x + 1, y);
        return;
    }
    for (int i = 5; i >= 1; i--) {
        if (paper[i] == 0) continue;
        if (y + i > 10 || x + i > 10) continue;

        bool flag = true;
        for (int j = 0; j < i; j++) {
            for (int k = 0; k < i; k++) {
                if (map[y + j][x + k] == 0) {
                    flag = false;
                    break;
                }
            }
            if (!flag) break;
        }

        if (!flag) continue;
        for (int j = 0; j < i; j++)
            for (int k = 0; k < i; k++)
                map[y + j][x + k] = 0;

        paper[i]--;
        cnt++;
        dfs(x + i, y);
        for (int j = 0; j < i; j++)
            for (int k = 0; k < i; k++)
                map[y + j][x + k] = 1;

        paper[i]++;
        cnt--;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            cin >> map[i][j];

    dfs(0, 0);
    if (ans == INF) cout << "-1\n";
    else cout << ans << '\n';
    return 0;
}