#include <iostream>
#include <string>
#include <cstring>

using namespace std;
#define MAX 11
#define INF 987654321
int N, M, redX, redY, blueX, blueY, holeX, holeY, ans = INF;
char map[MAX][MAX];
string str;

void printMap() {
    cout << "\n----------print-----------\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++)
            cout << map[i][j] << " ";
        cout << '\n';
    }
    cout << "----------print-----------\n";
}

int min(int a, int b) {
    return a > b ? b : a;
}

bool toDown() {
    bool flag = false;
    // 우선 누가 먼저 움직여야 하는지 확인하자
    if (blueY < redY) { // 파란 공 우선 움직이기
        while (blueY > 0) {
            if (map[blueY - 1][blueX] == 'O')
                return false;
            if (map[blueY - 1][blueX] == '#' || map[blueY - 1][blueX] == 'R')
                break;
            map[blueY--][blueX] = '.';
            map[blueY][blueX] = 'B';
        }
        while (redY > 0) {
            if (map[redY - 1][redX] == 'O')
                return true;
            if (map[redY - 1][redX] == '#' || map[redY - 1][redX] == 'B')
                break;
            map[redY--][redX] = '.';
            map[redY][redX] = 'R';
        }
    } else {
        while (redY > 0) {
            if (map[redY - 1][redX] == 'O')
                flag = true;
            if (map[redY - 1][redX] == '#' || map[redY - 1][redX] == 'B')
                break;
            map[redY--][redX] = '.';
            map[redY][redX] = 'R';
        }

        while (blueY > 0) {
            if (map[blueY - 1][blueX] == 'O')
                flag = false;
            if (map[blueY - 1][blueX] == '#' || map[blueY - 1][blueX] == 'R')
                break;
            map[blueY--][blueX] = '.';
            map[blueY][blueX] = 'B';
        }
    }
    return flag;
}

bool toUp() {
    bool flag = false;
    if (blueY > redY) { // 파란 공 우선 움직이기
        while (blueY < N - 1) {
            if (map[blueY + 1][blueX] == 'O')
                return false;
            if (map[blueY + 1][blueX] == '#' || map[blueY + 1][blueX] == 'R')
                break;
            map[blueY++][blueX] = '.';
            map[blueY][blueX] = 'B';
        }
        while (redY < N - 1) {
            if (map[redY + 1][redX] == 'O')
                return true;
            if (map[redY + 1][redX] == '#' || map[redY + 1][redX] == 'B')
                break;
            map[redY++][redX] = '.';
            map[redY][redX] = 'R';
        }
    } else {
        while (redY < N - 1) {
            if (map[redY + 1][redX] == 'O')
                flag = true;
            if (map[redY + 1][redX] == '#' || map[redY + 1][redX] == 'B')
                break;
            map[redY++][redX] = '.';
            map[redY][redX] = 'R';
        }
        while (blueY < N - 1) {
            if (map[blueY + 1][blueX] == 'O')
                flag = false;
            if (map[blueY + 1][blueX] == '#' || map[blueY + 1][blueX] == 'R')
                break;
            map[blueY++][blueX] = '.';
            map[blueY][blueX] = 'B';
        }
    }
    return flag;
}

bool toRight() {
    bool flag = false;
    if (blueX > redX) { //파란공 먼저 움직이자
        while (blueX < M - 1) {
            if (map[blueY][blueX + 1] == 'O')
                return false;
            if (map[blueY][blueX + 1] == '#' || map[blueY][blueX + 1] == 'R')
                break;
            map[blueY][blueX++] = '.';
            map[blueY][blueX] = 'B';
        }
        while (redX < M - 1) {
            if (map[redY][redX + 1] == 'O')
                return true;
            if (map[redY][redX + 1] == '#' || map[redY][redX + 1] == 'B')
                break;
            map[redY][redX++] = '.';
            map[redY][redX] = 'R';
        }
    } else {
        while (redX < M - 1) {
            if (map[redY][redX + 1] == 'O')
                flag = true;
            if (map[redY][redX + 1] == '#' || map[redY][redX + 1] == 'B')
                break;
            map[redY][redX++] = '.';
            map[redY][redX] = 'R';
        }
        while (blueX < M - 1) {
            if (map[blueY][blueX + 1] == 'O')
                flag = false;
            if (map[blueY][blueX + 1] == '#' || map[blueY][blueX + 1] == 'R')
                break;
            map[blueY][blueX++] = '.';
            map[blueY][blueX] = 'B';
        }
    }
    return flag;
}

bool toLeft() {
    bool flag = false;
    if (blueX < redX) { //파란공 먼저 움직이자
        while (blueX > 0) {
            if (map[blueY][blueX - 1] == 'O')
                return false;
            if (map[blueY][blueX - 1] == '#' || map[blueY][blueX - 1] == 'R')
                break;
            map[blueY][blueX--] = '.';
            map[blueY][blueX] = 'B';
        }
        while (redX > 0) {
            if (map[redY][redX - 1] == 'O')
                return true;
            if (map[redY][redX - 1] == '#' || map[redY][redX - 1] == 'B')
                break;
            map[redY][redX--] = '.';
            map[redY][redX] = 'R';
        }
    } else {
        while (redX > 0) {
            if (map[redY][redX - 1] == 'O')
                flag = true;
            if (map[redY][redX - 1] == '#' || map[redY][redX - 1] == 'B')
                break;
            map[redY][redX--] = '.';
            map[redY][redX] = 'R';
        }
        while (blueX > 0) {
            if (map[blueY][blueX - 1] == 'O')
                flag = false;
            if (map[blueY][blueX - 1] == '#' || map[blueY][blueX - 1] == 'R')
                break;
            map[blueY][blueX--] = '.';
            map[blueY][blueX] = 'B';
        }
    }
    return flag;
}

int inverse(int a) {
    if (a == 0) return 1;
    if (a == 1) return 0;
    if (a == 2) return 3;
    if (a == 3) return 2;
    return -1;
}

void dfs(int cnt, bool over, int dir) {
    if (cnt >= 11)
        return;
    if (over)
        return;
    char store[MAX][MAX];
    memcpy(store, map, sizeof(map));

    bool tmp = false;
    int d = -1;
    for (int i = 0; i < 4; i++) { // 0,1,2,3 --> 0일때 위로, 1일때 아래로, 2일때 왼쪽, 3일때 오른쪽
        if (i == dir) continue;
        if (i == inverse(dir)) continue;
        switch (i) {
            case 0:
                d = 0;
                tmp = toUp();
                break;
            case 1:
                d = 1;
                tmp = toDown();
                break;
            case 2:
                d = 2;
                tmp = toRight();
                break;
            case 3:
                d = 3;
                tmp = toLeft();
                break;
        }
        bool changed = false;
        for (int j = 0; j < N; j++)
            for (int k = 0; k < M; k++)
                if (map[j][k] != store[j][k])
                    changed = true;

        if (tmp) {
            ans = min(ans, cnt + 1);
            return;
        }
        if (changed)
            dfs(cnt + 1, tmp, d);
        memcpy(map, store, sizeof(store));
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        cin >> str;
        for (int j = 0; j < str.length(); j++) {
            map[i][j] = str[j];
            if (str[j] == 'R') {
                redX = j;
                redY = i;
            } else if (str[j] == 'B') {
                blueX = j;
                blueY = i;
            } else if (str[j] == 'O') {
                holeX = j;
                holeY = i;
            }
        }
    }

//    toUp();
//    printMap();
//    toRight();
//    printMap();
//    toDown();
//    printMap();
//    toRight();
//    printMap();
//    toUp();
//    printMap();
//    toLeft();
//    printMap();
//    toUp();
//    printMap();
    dfs(0, false, -1);
    if (ans >= 11)
        cout << "-1\n";
    else
        cout << ans << '\n';
    return 0;
}