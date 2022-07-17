/**
 * 1074 Z
 * 분할정복
 */
#include <iostream>

using namespace std;
int N, r, c, cnt;

void calculate(int size, int x, int y) {
    if (x == c && y == r) {
        cout << cnt << "\n";
        exit(0);
    }

    if (x <= c && y <= r && x + size > c && y + size > r) {
        int next_size = size / 2;
        calculate(next_size, x, y);
        calculate(next_size, x + next_size, y);
        calculate(next_size, x, y + next_size);
        calculate(next_size, x + next_size, y + next_size);
    }
    cnt += size * size;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> r >> c;
    int size = 1 << N;
    calculate(size, 0, 0);

    return 0;
}