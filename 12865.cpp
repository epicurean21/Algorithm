/**
 * 12865 평범한 배낭
 * 0/1 Knapsack 문제
 * Dynamic Programming [Divide and Conquer + Memoization]
 */

#include <iostream>

using namespace std;
#define MAX 101
#define INF 100001
int N, K, W, V, dp[MAX][INF];
pair<int, int> item[MAX];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> K;
    for (int i = 1; i <= N; i++) {
        cin >> W >> V;
        item[i] = {W, V};
    }

    for (int i = 1; i <= N; i++) {
        int w = item[i].first;
        int v = item[i].second;

        for (int j = 0; j <= K; j++) {
            if (w > j)
                dp[i][j] = dp[i - 1][j];
            else
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - w] + v);
        }
    }
    cout << dp[N][K];

    return 0;
}