/**
 * 14550 마리오 파티
 * 다이나믹 프로그래밍
 *
 */
#include "iostream"
#include "algorithm"

using namespace std;
#define MAX 205
int N, S, T;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    while (1) {
        cin >> N;
        if (N == 0) break;
        cin >> S >> T;

        int arr[MAX] = {0,}, dp[MAX][MAX]; // dp[x][y] = x 번째 시도해서 y 위치에서의 최댓값

        for (int i = 1; i <= N; i++) cin >> arr[i]; // 배열 입력

        for (int i = 0; i < T; i++) { // T 번 던지는데, dp 배열 초기화
            dp[i][0] = 0; // i번 던져서 시작점이면 최댓값 0
            for (int j = 1; j < N + 2; j++) dp[i][j] = INT32_MIN; // i번 던져서 j 위치까지 모두 -INF
        }

        for (int i = 1; i <= S; i++) dp[0][i] = arr[i]; // 0번 던졌을 때 주사위 가능성 (위치)는 입력배열과 같음


        for (int i = 1; i < T; i++) { // T 번 던짐
            for (int j = 1; j <= N + 1; j++) { // 각 위치
                for (int k = 1; k <= S; k++) { // 주사위 던졌을 때 나올값
                    if (j - k < 0 || dp[i - 1][j - k] == INT32_MIN) continue; // 이전 위치가 음수거나 이전 값이 -INF면 스킵
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - k] + arr[j]);
                    // Max ( i번 던져서 j 위치의 값과 이전 위치에서 현재 값을 더한것중 큰 값)
                }
            }
        }

        cout << dp[T - 1][N + 1] << '\n';
    }

    return 0;
}