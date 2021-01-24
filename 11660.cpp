#include <iostream>
#include <cstring>

using namespace std;
#define MAX 1030
int N, M, x_1, y_1, x_2, y_2;
int map[MAX][MAX], sum[MAX][MAX];

// sum[i][j] : 1행 1열부터 i 행 j 열까지의 합
// 누적합을 활용

int cal(int a, int b, int c, int d) {
    return sum[c][d] - sum[c][b - 1] - sum[a - 1][d] + sum[a - 1][b - 1];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cin >> map[i][j];
            sum[i][j] = sum[i][j - 1] + sum[i - 1][j] - sum[i - 1][j - 1] + map[i][j];
        }
    }
    for (int i = 0; i < M; i++) {
        cin >> x_1 >> y_1 >> x_2 >> y_2;
        cout << cal(x_1, y_1, x_2, y_2) << '\n';
    }
    return 0;
}