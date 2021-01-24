#include <iostream>
#include <cstring>

using namespace std;
#define MOD 1000000007
#define MAX 10002
/*
 * 제단
 * 특징
 * N이 최대 10,000일때 아무리 제단을 올리고싶어도 최대 5천까지밖에 못 올린다. 왜냐? 2씩 (앞, 뒤)로 줄어드니까
 */
int N, h[MAX];
int dp[MAX][MAX / 2]; // dp[i][j]: i번째 제단까지 진행을 했을 때 높이가 j인 경우의 수

// !! 최적화 !! //
int dp2[2][MAX / 2], pre = 0, cur = 1;

int min(int a, int b) {
    return a > b ? b : a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> h[i];

        // 양쪽 끝 비교 0 이 아니면 ==> 0
        if (h[i] > min(i, N - i)) {
            cout << "0\n";
            return 0;
        }
    }

    memset(dp2, 0, sizeof(dp2));
    dp2[pre][0] = 1;
    for (int i = 2; i <= N; i++) {
        // dp[cur][xx]
        int start = 0, end = N / 2;

        //cur 메모리를 초기화 해준다.
        for (int j = 0; j <= MAX / 2; j++)
            dp2[cur][j] = 0;

        if (h[i] != -1)
            start = h[i], end = h[i];
        for (int j = start; j <= end; j++) {
            if (j - 1 >= 0) {
                dp2[cur][j] += dp2[pre][j - 1];
                dp2[cur][j] %= MOD;
            }
            dp2[cur][j] += dp2[pre][j];
            dp2[cur][j] %= MOD;
            if (j + 1 <= 5000) {
                dp2[cur][j] += dp2[pre][j + 1];
                dp2[cur][j] %= MOD;
            }
        }
        cur ^= 1;
        pre ^= 1;
    }

    cout << dp2[pre][0] << "\n";


// 메모리 사용 197484KB	시간 336ms 전체를 다 쓴경우
/*
    memset(dp, 0, sizeof(dp));
    dp[1][0] = 1;
    // i번째 제단에서 가능한 높이 경우의 수를 넣는다
    for (int i = 2; i <= N; i++) {
        if (h[i] != -1) {
            int j = h[i];
            if (j - 1 >= 0)
                dp[i][j] += dp[i - 1][j - 1], dp[i][j] %= MOD;

            dp[i][j] += dp[i - 1][j], dp[i][j] %= MOD;

            if (j + 1 <= 5000)
                dp[i][j] += dp[i - 1][j + 1], dp[i][j] %= MOD;
            // if(j != h[i] == > 계산하면 안된다.
            // else 계산 해야한다. dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j] + dp[i - 1][j + 1];
        } else {
            for (int j = 0; j <= N / 2; j++) {
                // i번째 재단이 j 의 높이를 갖는 경우의 수
                // j --> 이전의 높이가 j + 1, j, j - 1 합쳐지는 경우의 수
                if (j - 1 >= 0)
                    dp[i][j] += dp[i - 1][j - 1], dp[i][j] %= MOD;

                dp[i][j] += dp[i - 1][j], dp[i][j] %= MOD;

                if (j + 1 <= 5000)
                    dp[i][j] += dp[i - 1][j + 1], dp[i][j] %= MOD;
            }
        }
    }

    cout << dp[N][0] << '\n';
*/
    return 0;
}