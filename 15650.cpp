/**
 * 15650 N과 M (2)
 * 백트래킹, 구현
 */
#include <iostream>

using namespace std;
int N, M, chk[9], arr[9];

void dfs(int count) {
    if (count - 1 == M) {
        for (int i = 1; i <= M; i++)
            cout << arr[i] << " ";
        cout << '\n';
        return;
    }
    for (int i = 1; i <= N; i++) {
        if (!chk[i]) {
            if (arr[count - 1] < i) {
                chk[i] = true;
                arr[count] = i;
                dfs(count + 1);
                chk[i] = false;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    dfs(1);

    return 0;
}