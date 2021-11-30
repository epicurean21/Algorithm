/**
 * 15649 N과 M (1)
 * 백트래킹
 */

#include <iostream>

using namespace std;
int N, M, chk[9], arr[9];

void dfs(int idx) {
    if (idx == M) {
        for (int i = 0; i < M; i++)
            cout << arr[i] << " ";
        cout << '\n';
        return;
    }
    for (int i = 1; i <= N; i++) {
        if (!chk[i]) {
            chk[i] = true;
            arr[idx] = i;
            dfs(idx + 1);
            chk[i] = false;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    dfs(0);

    return 0;
}