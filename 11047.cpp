/**
 * 11047: 동전 0
 * 그리디 알고리즘
 */
#include <iostream>

using namespace std;
#define MAX 11
int N, K, coin[MAX], idx, ans;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> K;
    for (int i = 0; i < N; i++) {
        cin >> coin[i];
        if (coin[i] > K && idx == 0)
            idx = i - 1;
    }
    if (idx == 0)
        idx = N - 1;

    while (K) {
        ans += (K / coin[idx]);
        K -= (K / coin[idx]) * coin[idx];
        idx--;
    }

    cout << ans << '\n';

    return 0;
}