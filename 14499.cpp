#include <iostream>

using namespace std;
#define MAX 22
int N, M, x, y, K, cmd, map[MAX][MAX], curTop = 1, cx, cy;
int dx[] = {0, 1, -1, 0, 0}, dy[] = {0, 0, 0, -1, 1}, dice[7] = {0,};

void move(int dir) {
    int tmp[7];
    for (int i = 1; i < 7; i++)
        tmp[i] = dice[i];
    if (dir == 1) {
        dice[1] = tmp[4];
        dice[3] = tmp[1];
        dice[4] = tmp[6];
        dice[6] = tmp[3];
    } else if (dir == 2) {
        dice[1] = tmp[3];
        dice[3] = tmp[6];
        dice[4] = tmp[1];
        dice[6] = tmp[4];
    } else if (dir == 3) {
        dice[1] = tmp[5];
        dice[2] = tmp[1];
        dice[5] = tmp[6];
        dice[6] = tmp[2];
    } else {
        dice[1] = tmp[2];
        dice[2] = tmp[6];
        dice[5] = tmp[1];
        dice[6] = tmp[5];
    }
}

int solve(int dir, int curx, int cury) {
    int nx = curx + dx[dir];
    int ny = cury + dy[dir];
    if (nx < 0 || nx >= M || ny < 0 || ny >= N) // 범위를 벗어났다.
        return -1;
    //실제로 굴리자
    move(dir);
    // 첫번째 주사위 복사
    curTop = dice[1];
    int onBoard = map[ny][nx];
    if (onBoard == 0) {
        map[ny][nx] = dice[6];
    } else {
        dice[6] = onBoard;
        map[ny][nx] = 0;
    }
    cx = nx;
    cy = ny;
    return curTop;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M >> y >> x >> K;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            cin >> map[i][j];
    cx = x, cy = y;
    while (K--) {
        cin >> cmd;
        int ans = solve(cmd, cx, cy);
        if (ans == -1) continue;
        cout << ans << '\n';
    }
    return 0;
}