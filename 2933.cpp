#include <iostream>
#include <string>
#include <queue>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
#define MAX 102
#define INF 12341
int Y, X, N, shoot[MAX], h;
char map[MAX][MAX];
bool been[MAX][MAX];
int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};
vector<pair<int, int>> vec;

int min(int a, int b) {
    return a > b ? b : a;
}

int find_min() {
    int min_move = INF;
    bool same_cluster[MAX][MAX];
    memset(same_cluster, false, sizeof(same_cluster));

    for (int i = 0; i < vec.size(); i++) {
        int curx = vec[i].second;
        int cury = vec[i].first;
        same_cluster[cury][curx] = true;
    }

    for (int i = 0; i < vec.size(); i++) {
        int curx = vec[i].second;
        int cury = vec[i].first;

        int tmp = cury;
        while (1) {
            if (map[tmp + 1][curx] == 'x' || tmp == Y) {
                if (same_cluster[tmp + 1][curx]) // 같은 cluster애다
                    break;
                min_move = min(tmp - cury, min_move);
                break;
            }
            tmp++;
        }
    }
    return min_move;
}

void dfs(int x, int y) {
    been[y][x] = true;
    vec.push_back({y, x});

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx < 1 || nx > X || ny < 1 || ny > Y) continue;
        if (been[ny][nx]) continue;
        if (map[ny][nx] == '.') continue;
        been[ny][nx] = true;
        dfs(nx, ny);
    }
}

void move(int height) {
    for (int i = 0; i < vec.size(); i++) {
        int curx = vec[i].second;
        int cury = vec[i].first;

        map[cury][curx] = '.';
        map[cury + height][curx] = 'x';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> Y >> X;
    for (int i = 1; i <= Y; i++) {
        string str;
        cin >> str;
        for (int j = 1; j <= X; j++)
            map[i][j] = str[j - 1];
    }

    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> h;
        shoot[i] = Y - h + 1;
    }

    for (int i = 0; i < N; i++) {
        int shooting = shoot[i];
        int x = 0;
        bool destroy = true;
        if (i % 2 == 0) { // 왼쪽
            for (int j = 1; j <= X; j++)
                if (map[shooting][j] == 'x') {
                    map[shooting][j] = '.';
                    x = j;
                    destroy = false;
                    break;
                }
        } else { // 오른쪽
            for (int j = X; j >= 1; j--)
                if (map[shooting][j] == 'x') {
                    map[shooting][j] = '.';
                    x = j;
                    destroy = false;
                    break;
                }
        }

        if (destroy) continue;
        for (int j = 0; j < 4; j++) {
            int nx = x + dx[j];
            int ny = shooting + dy[j];

            if (nx <= 0 || nx > X || ny <= 0 || ny > Y) continue;
            if (map[ny][nx] == '.') continue;
            memset(been, false, sizeof(been));
            vec.clear();
            dfs(nx, ny);
            sort(vec.begin(), vec.end(), greater<pair<int, int>>());
            if (vec[0].first == Y) continue;
            int min_move = find_min(); // 최소 움직임 파악
            move(min_move);
        }
    }
    for (int i = 1; i <= Y; i++) {
        for (int j = 1; j <= X; j++)
            cout << map[i][j];
        cout << '\n';
    }
    return 0;
}