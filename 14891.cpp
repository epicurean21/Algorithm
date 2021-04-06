#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int wheel[4][8], K, idx, dir;
int cur_dir[4] = {0, 0, 0, 0};

int score() {
    int cnt = 0;
    for (int i = 0; i < 4; i++)
        if (wheel[i][cur_dir[i]] == 1)
            cnt += (int) pow(2, i);
    return cnt;
}

void turn(int gear, int direction) {
    if (direction == 1) {
        int cur = cur_dir[gear] - 1; // 시계방향 12시만 바꿔주기
        if (cur < 0)
            cur = 7;
        cur_dir[gear] = cur;
    } else {
        int cur = cur_dir[gear] + 1;
        cur %= 8;
        cur_dir[gear] = cur;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    for (int i = 0; i < 4; i++) {
        string str;
        cin >> str;
        for (int j = 0; j < str.length(); j++)
            wheel[i][j] = str[j] - '0';
    }

    cin >> K;
    while (K--) {
        cin >> idx >> dir;
        int pre_l = wheel[idx - 1][(cur_dir[idx - 1] + 6) % 8];
        int pre_r = wheel[idx - 1][(cur_dir[idx - 1] + 2) % 8];
        int pre_dir = dir;
        for (int i = idx; i < 4; i++) { // 오른쪽
            int cur_l = wheel[i][(cur_dir[i] + 6) % 8];
            int cur_r = wheel[i][(cur_dir[i] + 2) % 8];
            int cur_dir = pre_dir * -1;
            if (pre_r != cur_l) { // 서로 극이 다름 즉 회전해야함
                pre_r = cur_r;
                pre_dir = cur_dir;
                turn(i, cur_dir);// 반대방향으로 회전
            } else {
                break;
            }
        }
        pre_l = wheel[idx - 1][(cur_dir[idx - 1] + 6) % 8];
        pre_dir = dir;
        for (int i = idx - 2; i >= 0; i--) { // 왼쪽
            int cur_l = wheel[i][(cur_dir[i] + 6) % 8];
            int cur_r = wheel[i][(cur_dir[i] + 2) % 8];
            int cur_dir = pre_dir * -1;
            if (pre_l != cur_r) { // 서로 극이 다름 즉 회전해야함
                pre_l = cur_l;
                pre_dir = cur_dir;
                turn(i, cur_dir);// 반대방향으로 회전
            } else {
                break;
            }
        }
        turn(idx - 1, dir);
    }

    cout << score() << '\n';
    return 0;
}