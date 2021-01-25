#include <iostream>

using namespace std;
#define MAX 1001
#define MOD 10007
int N, T, dp[MAX];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N;
    dp[1] = 1;
    dp[0] = 1;
    for (int i = 2; i <= N; i++)
        dp[i] = (dp[i - 1] + dp[i - 2] * 2) % MOD;
    cout << dp[N] << '\n';
    return 0;
}