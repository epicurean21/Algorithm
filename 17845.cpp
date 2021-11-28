/**
 * 17845 수강 과목
 * 배낭문제, 다이나믹 프로그래밍
 * 0/1 Knapsack problem
 */
#include <iostream>

using namespace std;
#define MAX 10001
#define INF 100002
int N, K, I, T, dp[MAX][INF];
pair<int, int> courses[MAX];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> K;
    for (int i = 1; i <= K; i++) {
        cin >> I >> T;
        courses[i] = {I, T};
    }

    for (int i = 1; i <= K; i++) {
        int importance = courses[i].first;
        int time_cost = courses[i].second;

        for (int j = 0; j <= N; j++) {
            if (time_cost > j)
                dp[i][j] = dp[i - 1][j];
            else
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - time_cost] + importance);
        }
    }

    cout << dp[K][N];

    return 0;
}