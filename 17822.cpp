/**
 * 17822 원판 돌리기
 * 구현, 시뮬레이션
 * 졸라 까다롭네;.. 재밌게 풀었음 그래도
 */

#include <iostream>

using namespace std;
#define MAX 55
int N, M, T, x, d, k;
float arr[MAX][MAX];
int dx[] = {1, 0, 0, -1}, dy[] = {0, 1, -1, 0};
bool is_changed;

void rotate(int x) {
    float temp = arr[x][M - 1];
    for (int i = M - 1; i > 0; i--)
        arr[x][i] = arr[x][i - 1];
    arr[x][0] = temp;
}

void dfs(int x, int y, float value) {
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i], ny = y + dy[i];

        if (ny == -1) ny = M - 1;
        if (ny == M) ny = 0;

        if (nx < 0 || nx >= N || arr[nx][ny] != value) continue;
        if (arr[x][y] != -1) {
            is_changed = true;
            arr[x][y] = -1;
        }
        arr[nx][ny] = -1;
        dfs(nx, ny, value);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M >> T;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            cin >> arr[i][j];

    for (int i = 0; i < T; i++) {
        cin >> x >> d >> k;

        if (d == 1) k = M - k;
        for (int j = 1; (x * j) <= N; j++)
            for (int kk = 0; kk < k; kk++) rotate(x * j - 1);

        is_changed = false;

        for (int x = 0; x < N; x++)
            for (int y = 0; y < M; y++)
                if (arr[x][y] != -1) dfs(x, y, arr[x][y]);

        if (!is_changed) {
            float avg = 0, num = 0;
            for (int x = 0; x < N; x++)
                for (int y = 0; y < M; y++)
                    if (arr[x][y] != -1) {
                        num++;
                        avg += arr[x][y];
                    }

            if (num > 1) {
                avg = avg / num;
                for (int x = 0; x < N; x++)
                    for (int y = 0; y < M; y++) {
                        if (arr[x][y] == -1) continue;
                        else if (arr[x][y] < avg) arr[x][y]++;
                        else if (arr[x][y] > avg) arr[x][y]--;
                        else if (arr[x][y] == avg) {}
                    }
            }

        }
    }

    int ans = 0;
    for (int x = 0; x < N; x++)
        for (int y = 0; y < M; y++)
            if (arr[x][y] != -1) ans += arr[x][y];
    cout << ans;

    return 0;
}