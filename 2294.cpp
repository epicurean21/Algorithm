/**
 * 2294 동전2
 * 다이나믹 프로그래밍
 *
 * dp 배열: dp[i] = i원을 만들 수 있는 최소 동전의 개수
 * dp 식: dp[i] = min (dp[i - k] + 1, dp[i])
 * 즉, i번째를 k원으로 만드려면, dp[i - k], k원까지 만든 최소값에 한개의 코인을 더 했을때 또는 dp[i]
 */
#include "iostream"
#include "algorithm"
using namespace std;
#define MAX 100001
int n, k, dp[MAX], coins[101];

void init() {
    for (int i = 1; i <= k; i++) dp[i] = MAX;
    for (int i = 1; i <= n; i++) dp[coins[i]] = 1;
}

void calculate_dp() {
    for (int i = 1; i <= n; i++)
        for (int j = coins[i]; j <= k; j++)
            dp[j] = min(dp[j - coins[i]] + 1, dp[j]);
}

int main() {
    cin.tie(nullptr)->ios::sync_with_stdio(false);

    cin >> n >> k;
    for (int i = 1; i <= n; i++) cin >> coins[i];
    init();

    calculate_dp();
    if (dp[k] == MAX) cout << "-1\n";
    else cout << dp[k] << "\n";

    return 0;
}