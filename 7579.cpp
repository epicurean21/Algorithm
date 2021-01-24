#include <iostream>

#define ll long long
#define MAX 102
#define INF 987654321
using namespace std;
int N, M, c[MAX], m[MAX], dp[MAX][MAX * 100], ans = INF; // dp[i][j]는 i번째 프로그램 종료시 j의 메모리로 얻는 최소 시간.

int min(int a, int b) {
    return a > b ? b : a;
}

// [i][j] : i번째 앱까지 고려했을 때(= 대상으로 했을 때) cost j로 확보할 수 있는 최대 메모리
// i번째 앱을 사용하지 않은 경우
// 또는 j번째 앱을 사용한 경우
// 이 둘중 큰 값
void DP() {
    for (int i = 1; i <= N; i++) {
        for (int j = 0; j <= 10000; j++) {
            if (j - c[i] >= 0)
                dp[i][j] = max(dp[i][j], dp[i - 1][j - c[i]] + m[i]);

            dp[i][j] = max(dp[i][j], dp[i - 1][j]);

            if (dp[i][j] >= M)
                ans = min(ans, j);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    for (int i = 1; i <= N; i++)
        cin >> m[i];
    for (int i = 1; i <= N; i++)
        cin >> c[i];

    dp[1][c[1]] = m[1];
    DP();
    cout << ans << '\n';

    return 0;
}

