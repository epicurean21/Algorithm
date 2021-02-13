#include <iostream>
#include <algorithm>

using namespace std;
#define MAX 40001
int N, dp[MAX], port[MAX], idx = 1;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    for (int i = 1; i <= N; i++)
        cin >> port[i];
    dp[idx] = port[idx];
    for (int i = 2; i <= N; i++) {
        if (dp[idx] < port[i])
            dp[++idx] = port[i];
        else {
            int tmp = lower_bound(dp + 1, dp + idx + 1, port[i]) - dp;
            dp[tmp] = port[i];
        }
    }
    cout << idx << '\n';
    return 0;
}