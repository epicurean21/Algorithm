/**
 * 2580 스도쿠
 * 구현, 백트래킹
 */
#include <iostream>

using namespace std;
#define MAX 9
int map[MAX][MAX];
bool row[MAX][MAX], col[MAX][MAX], sqr[MAX][MAX];

void print() {
    for (auto &i: map) {
        for (int j: i)
            cout << j << " ";
        cout << '\n';
    }
}

void solve(int cnt) {
    int x = cnt % MAX;
    int y = cnt / MAX;
    if (cnt == MAX * MAX) {
        print();
        exit(0);
    }
    if (map[y][x] == 0) {
        for (int i = 1; i <= MAX; i++) {
            if (!row[y][i] && !col[x][i] && !sqr[(y / 3) * 3 + (x / 3)][i]) {
                row[y][i] = col[x][i] = sqr[(y / 3) * 3 + (x / 3)][i] = true;
                map[y][x] = i;
                solve(cnt); // 다음으로 들어가기 --> 실패 return 되면, 이곳으로 다시온다

                map[y][x] = 0; // 안되는 숫자이기 때문에 되돌려놓는다
                row[y][i] = col[x][i] = sqr[(y / 3) * 3 + (x / 3)][i] = false;
            }
        }
    } else solve(cnt + 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            cin >> map[i][j];
            if (map[i][j]) {
                row[i][map[i][j]] = true; // 가로(row) 줄에 해당 숫자 존재함
                col[j][map[i][j]] = true; // 세로(col) 줄에 해당 숫자 존재함
                sqr[(i / 3) * 3 + (j / 3)][map[i][j]] = true; // 3*3 영역에 해당 숫자 존재함
            }
        }
    }

    solve(0);
    print();

    return 0;
}