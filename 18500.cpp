/**
 * 18500: 미네랄 2
 * 구현, 시뮬레이션, DFS, 그래프 이론
 */
#include <iostream>

using namespace std;
#define MAX 102

int R, C, N, map[MAX][MAX], level;
char input;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> R >> C;
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            cin >> input;
            if (input == 'x')
                map[i][j] = 1;
        }
    }

    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> level;
    }

    return 0;
}