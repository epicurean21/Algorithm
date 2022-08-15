/**
 * 9663 nQueen
 * 백트래킹
 */
#include <iostream>

using namespace std;
#define MAX 15
int N, row[MAX], ans;

bool isPromising(int i) {
    for (int j = 0; j < i; j++) // 0 ~ i-1번째 줄까지 기존 놓여진 퀸을 확인한다.
        if (row[j] == row[i] || abs(row[i] - row[j]) == (i - j)) // 같은 줄에 있다거나,
            return false;
    return true;
}

void nQueen_Pruning(int i) {
    if (i == N) // N개 줄까지 왔다면, 정답 수를 추가
        ans += 1;
    else {
        for (int j = 0; j < N; j++) {
            row[i] = j; // i번째 줄 j 번째 칸에 퀸을 놓았다.
            if (isPromising(i)) // 해당 값이 유효한가 ?
                nQueen_Pruning(i + 1); // 유효하다면 다음 줄로 넘어간다.
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> N;
    nQueen_Pruning(0); // 0 번째 줄부터 확인
    cout << ans << "\n";

    return 0;
}