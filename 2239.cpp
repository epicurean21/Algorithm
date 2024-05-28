/**
 * 2239 스도쿠
 * 백트래킹, 구현
 */
#include <iostream>

using namespace std;

int sudoku[9][9];
bool row[9][9], col[9][9], sqr[9][9];

void print() {
    for (auto &i: sudoku) {
        for (int j: i)
            cout << j;
        cout << '\n';
    }
    exit(0);
}

void check(int cnt) {
    int x = cnt / 9;
    int y = cnt % 9;

    if (cnt == 81) {
        print();
    }

    if (sudoku[x][y] == 0) {
        for (int i = 1; i <= 9; i++) {
            if (!row[x][i] && !col[y][i] && !sqr[(x / 3) * 3 + (y / 3)][i]) {
                row[x][i] = true;
                col[y][i] = true;
                sqr[(x / 3) * 3 + (y / 3)][i] = true;
                sudoku[x][y] = i;
                check(cnt + 1);

                sudoku[x][y] = 0;
                row[x][i] = false;
                col[y][i] = false;
                sqr[(x / 3) * 3 + (y / 3)][i] = false;
            }
        }
    } else
        check(cnt + 1);
}

int main() {
    cin.tie(NULL)->sync_with_stdio(false);

    for (int i = 0; i < 9; i++) {
        string str;
        cin >> str;
        for (int j = 0; j < 9; j++) {
            sudoku[i][j] = str[j] - '0';
            if (sudoku[i][j] != 0) {
                row[i][sudoku[i][j]] = true;
                col[j][sudoku[i][j]] = true;
                sqr[(i / 3) * 3 + (j / 3)][sudoku[i][j]] = true;
            }
        }
    }
    check(0);

    return 0;
}