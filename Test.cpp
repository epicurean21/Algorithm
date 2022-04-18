/**
 * 16967 배열 복원하기
 * 구현
 */
#include <iostream>

using namespace std;
#define MAX 604
int H, W, X, Y, B[MAX][MAX];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> H >> W >> X >> Y;
    for (int i = 0; i < H + X; i++)
        for (int j = 0; j < W + Y; j++)
            cin >> B[i][j];

    for (int i = X; i < H; i++)
        for (int j = Y; j < W; j++)
            B[i][j] -= B[i - X][j - Y];

    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++)
            cout << B[i][j] << " ";
        cout << '\n';
    }

    return 0;
}