/**
 * 17822 원판 돌리기
 * 구현, 시뮬레이션
 *
 */

#include <iostream>
#include <vector>

using namespace std;
#define MAX 52
int N, M, T, x, d, k, number_count, dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};
bool chk[MAX][MAX];
vector<vector<int>> frisbee;

int abs(int a) {
    return a < 0 ? -a : a;
}

void print_map() {

    for (int i = 1; i <= N; i++) {
        cout << i << "번째 판\n";
        for (int j = 0; j < M; j++) {
            cout << frisbee[i][j] << " ";
        }
        cout << '\n';
    }
}

bool do_magical() { // 인접한 수가 있는 경우 지운다.
    bool option = false; // 1 번 옵션. 지우기

    for (int i = 1; i <= N; i++) {

    }
}

void rotate(int xi, int di, int ki) {
    int mul = 1;
    while (xi <= N) {
        vector<int> tmp;
        int pointer = 0;

        if (di) pointer = ki; // 반시계
        else pointer = M - ki; // 시계

        for (int i = 0; i < M; i++) {
            tmp.emplace_back(frisbee[xi][pointer]);
            pointer++;
            pointer %= M;
        }
        frisbee[xi] = tmp;

        xi *= ++mul;
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M >> T; // N개 원판, 각 원판[i] 에 M개 정수, T번 회전

    number_count = N * M;
    frisbee.resize(N + 1);

    for (int i = 1; i <= N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> x;
            frisbee[i].emplace_back(x);
        }
    }
    for (int i = 0; i < T; i++) {
        cin >> x >> d >> k;
        rotate(x, d, k);
    }

    return 0;
}