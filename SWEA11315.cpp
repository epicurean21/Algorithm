#include <iostream>
#include <string>

using namespace std;
#define MAX 21
int T, N;
char map[MAX][MAX];

void reset() {
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++)
            map[i][j] = ' ';
    }
}

bool diagonal1(int x, int y) { // 대각선 좌상단우하단
    if (map[y][x] == '.')
        return false;
    for (int i = 0; i < 5; i++) {
        int nx = x + i;
        int ny = y + i;
        if (nx < 0 || nx >= N || ny < 0 | ny >= N)
            return false;
        if (map[ny][nx] == '.')
            return false;
    }
    return true;
}

bool diagonal2(int x, int y) { // 대각선 우상단 좌 하단
    if (map[y][x] == '.')
        return false;
    for (int i = 0; i < 5; i++) {
        int nx = x - i;
        int ny = y + i;
        if (nx < 0 || nx >= N || ny < 0 | ny >= N)
            return false;
        if (map[ny][nx] == '.')
            return false;
    }
    return true;
}

bool vertical(int x, int y) {
    if (map[y][x] == '.')
        return false;
    for (int i = 0; i < 5; i++) {
        int ny = y + i;
        if (x < 0 || x >= N || ny < 0 | ny >= N)
            return false;
        if (map[ny][x] == '.')
            return false;
    }
    return true;
}

bool horizontal(int x, int y) {
    if (map[y][x] == '.')
        return false;
    for (int i = 0; i < 5; i++) {
        int nx = x + i;
        if (nx < 0 || nx >= N || y < 0 | y >= N)
            return false;
        if (map[y][nx] == '.')
            return false;
    }
    return true;
}

bool solve() {
    bool tmp = false;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int x = j;
            int y = i;
            tmp = diagonal1(x, y);
            if (tmp == true)
                return true;
            tmp = diagonal2(x, y);
            if (tmp == true)
                return true;
            tmp = vertical(x, y);
            if (tmp == true)
                return true;
            tmp = horizontal(x, y);
            if (tmp == true)
                return true;
        }
    }
    return tmp;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> T;
    for (int t = 1; t <= T; t++) {
        cin >> N;
        reset();
        for (int i = 0; i < N; i++) {
            string str;
            cin >> str;
            for (int j = 0; j < N; j++)
                map[i][j] = str[j];
        }
        bool check = solve();
        if (check)
            cout << "#" << t << " YES\n";
        else
            cout << "#" << t << " NO\n";
    }
    return 0;
}