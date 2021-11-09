/**
 * 7682: 틱택토
 * 구현, 시뮬레이션, 백트레킹
 */

#include <iostream>
#include <string>

using namespace std;

string input;
char map[3][3], winner;
int dx[] = {1, -1, 0, 0, -1, 1, -1, 1}, dy[] = {1, -1, 1, -1, 1, -1, 0, 0};
bool flag, multi_winner;

void init() {
    flag = false;
    multi_winner = false;
    winner = ' ';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    while (cin >> input) {
        if (input == "end")
            break;

        int x_cnt = 0, o_cnt = 0, empty_cnt = 0;

        for (int i = 0; i < input.length(); i++) {
            map[i / 3][i % 3] = input[i];
            if (input[i] == 'X') x_cnt++;
            else if (input[i] == 'O') o_cnt++;
            else empty_cnt++;
        }

        if (o_cnt > x_cnt || x_cnt == 0 || o_cnt == 0 || x_cnt > 5 || o_cnt > 4) {
            cout << "invalid\n";
            continue;
        }

        init();
        for (int y = 0; y < 3; y++) {
            if (multi_winner) break;
            for (int x = 0; x < 3; x++) {
                if (multi_winner) break;
                if (map[y][x] == '.') continue;
                for (int k = 0; k < 8; k += 2) {
                    int nx1 = x + dx[k];
                    int ny1 = y + dy[k];
                    int nx2 = x + dx[k + 1];
                    int ny2 = y + dy[k + 1];
                    if (nx1 < 0 || nx1 > 2 || ny1 < 0 || ny1 > 2) continue;
                    if (nx2 < 0 || nx2 > 2 || ny2 < 0 || ny2 > 2) continue;

                    if (map[y][x] == map[ny1][nx1] && map[y][x] == map[ny2][nx2]) {
                        if (flag && winner != ' ' && winner != map[y][x]) {
                            multi_winner = true;
                            break;
                        }

                        if (map[y][x] == 'O')
                            winner = 'O';
                        else if (map[y][x] == 'X')
                            winner = 'X';

                        flag = true;
                    }
                }
            }
        }

        if (multi_winner) {
            cout << "invalid\n";
            continue;
        }

        if (!flag) {
            if (empty_cnt == 0 || x_cnt - o_cnt == 1)
                cout << "valid\n";
            else
                cout << "invalid\n";
        } else {
            if (winner == 'X') {
                if (x_cnt - o_cnt == 1)
                    cout << "valid\n";
                else
                    cout << "invalid\n";
            } else if (winner == 'O') {
                if (x_cnt == o_cnt)
                    cout << "valid\n";
                else
                    cout << "invalid\n";
            }
        }
    }

    return 0;
}