/*#include <iostream>
#include <string>
#include <cstring>

using namespace std;
#define MAX 11
#define INF 987654321
int N, M, redX, redY, blueX, blueY, ans = INF;
int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};
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
            if (map[blueY - 1][blueX] == '#')
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
            if (map[redY - 1][redX] == '#')
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
            if (map[blueY + 1][blueX] == '#')
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
            if (map[redY + 1][redX] == '#')
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
            if (map[blueY][blueX + 1] == '#')
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
            if (map[redY][redX + 1] == '#')
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
            if (map[blueY][blueX - 1] == '#')
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
        while (redX > 0) { // 빨간 공 먼저 움직이기
            if (map[redY][redX - 1] == 'O')
                flag = true;
            if (map[redY][redX - 1] == '#')
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

int dir_inverse(int d) {
    if (d == 0) return 2;
    else if (d == 1) return 3;
    else if (d == 2) return 0;
    else if (d == 3) return 1;
    else return -1;
}

bool move(int dir) {
    bool tmp = false;
    if (dir == 0)
        tmp = toUp();
    else if (dir == 1)
        tmp = toDown();
    else if (dir == 2)
        tmp = toRight();
    else if (dir == 3)
        tmp = toLeft();
    return tmp;
}

void dfs(int cnt, int dir) {
    if (cnt >= 11)
        return;
    if (cnt >= ans)
        return;
    char store[MAX][MAX];
    memcpy(store, map, sizeof(map));
    bool tmp = move(dir);
    if (tmp) {
        ans = min(ans, cnt);
        return;
    }

    for (int i = 0; i < 4; i++) {
        if (i == dir) continue;
        if (i == dir_inverse(dir)) continue;
        dfs(cnt + 1, i);
        memcpy(map, store, sizeof(map));
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
            }
        }
    }

    for (int i = 0; i < 4; i++)
        dfs(1, i);

    for (int i = 0; i < 4; i++)
    {
        if (i == dir) continue;
        if (i == dir_inverse(dir)) continue;

        Move(nRx, nRy, nBx, nBy, Cnt + 1, i);
    }
    if (ans >= 11)
        cout << "-1\n";
    else
        cout << ans << '\n';
    return 0;
}*/
#include<iostream>

#define MAX 10
using namespace std;

int N, M, Answer = 987654321;
char MAP[MAX][MAX];

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

pair<int, int> Red, Blue;

int Min(int A, int B) {
    if (A < B) return A;
    return B;
}

void Input() {
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> MAP[i][j];
            if (MAP[i][j] == 'R') {
                Red.first = i;
                Red.second = j;
                MAP[i][j] = '.';
            } else if (MAP[i][j] == 'B') {
                Blue.first = i;
                Blue.second = j;
                MAP[i][j] = '.';
            }
        }
    }
}

int Move_Dist(int x, int y, int xx, int yy) {
    return abs(x - xx) + abs(y - yy);
}

int Inverse_Direction(int Cur_D) {
    if (Cur_D == 0) return 1;
    else if (Cur_D == 1) return 0;
    else if (Cur_D == 2) return 3;
    else if (Cur_D == 3) return 2;
}

void Move(int Rx, int Ry, int Bx, int By, int Cnt, int dir) {
    if (Cnt >= Answer) return;
    if (Cnt > 10) return;

    bool Red_Flag = false;
    bool Blue_Flag = false;

    int nRx = Rx + dx[dir];
    int nRy = Ry + dy[dir];
    while (1) {
        if (MAP[nRx][nRy] == '#') break;
        if (MAP[nRx][nRy] == 'O') {
            Red_Flag = true;
            break;
        }
        nRx = nRx + dx[dir];
        nRy = nRy + dy[dir];
    }
    nRx = nRx - dx[dir];
    nRy = nRy - dy[dir];

    int nBx = Bx + dx[dir];
    int nBy = By + dy[dir];
    while (1) {
        if (MAP[nBx][nBy] == '#') break;
        if (MAP[nBx][nBy] == 'O') {
            Blue_Flag = true;
            break;
        }
        nBx = nBx + dx[dir];
        nBy = nBy + dy[dir];
    }
    nBx = nBx - dx[dir];
    nBy = nBy - dy[dir];

    if (Blue_Flag == true) return;
    else {
        if (Red_Flag == true) {
            Answer = Min(Answer, Cnt);
            return;
        }
    }

    if (nRx == nBx && nRy == nBy) {
        int Red_Dist = Move_Dist(Rx, Ry, nRx, nRy);
        int Blue_Dist = Move_Dist(Bx, By, nBx, nBy);

        if (Red_Dist > Blue_Dist) {
            nRx = nRx - dx[dir];
            nRy = nRy - dy[dir];
        } else {
            nBx = nBx - dx[dir];
            nBy = nBy - dy[dir];
        }
    }


    for (int i = 0; i < 4; i++) {
        if (i == dir) continue;
        if (i == Inverse_Direction(dir)) continue;

        Move(nRx, nRy, nBx, nBy, Cnt + 1, i);
    }
}

void Solution() {
    for (int i = 0; i < 4; i++) {
        int x = Red.first;
        int y = Red.second;
        int xx = Blue.first;
        int yy = Blue.second;

        Move(x, y, xx, yy, 1, i);
    }

    if (Answer > 10 || Answer == 987654321) Answer = -1;
    cout << Answer << '\n';
}

void Solve() {
    Input();
    Solution();
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    Solve();
    return 0;
}