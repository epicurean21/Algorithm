/**
 * 11060 점프점프
 * 다이나믹 프로그래밍
 */
#include "iostream"

using namespace std;
#define MAX 1001
int n, a[MAX], dp[MAX];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    dp[0] = 1;
    for (int i = 0; i < n; i++) {
        cin >> a[i];

        if (dp[i] == 0) continue;

        for (int j = 1; j <= a[i] && (i + j < MAX); j++)
            if (dp[i + j] > dp[i] + 1 || dp[i + j] == 0) // 이동 가능한 위치의 수가 아직 0 이거나, 현재 위치보다 많이 움직여야 하면
                dp[i + j] = dp[i] + 1; // 현재 위치 + 1 로 최적화
    }
    cout << (dp[n - 1] == 0 ? -1 : dp[n - 1] - 1) << '\n';
    return 0;
}