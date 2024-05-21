/**
 * 2792 보석상자
 * 이분탐색
 */
#include "bits/stdc++.h"

using namespace std;
#define MAX 300001
int N, M, jewels[MAX], ans;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> N >> M;
    for (int i = 0; i < M; i++) cin >> jewels[i];

    sort(jewels, jewels + M);

    int l = 1, r = jewels[M - 1];
    while (l <= r) {
        int m = (l + r) / 2;

        int cnt = 0;
        for (int i = 0; i < M; i++) {
            cnt += (jewels[i] / m);
            if (jewels[i] % m != 0) cnt++;
        }

        if (cnt <= N) {
            r = m - 1;
            ans = m;
        } else l = m + 1;
    }

    cout << ans << '\n';
    return 0;
}