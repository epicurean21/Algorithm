#include <iostream>
#include <string>

using namespace std;
#define MAX 1002
int N, M, ans;
string str;
int map[MAX][MAX], dp[MAX][MAX]; // dp[i][j] : 오른쪽 아래로 했을 때 가장 큰 정사각형

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a > b ? b : a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        cin >> str;
        for (int j = 1; j <= M; j++)
            map[i][j] = str[j - 1] - '0';
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            if (map[i][j] == 0) { // 우측 하단에 있는 점이 0 이면 정사각형 존재 X
                dp[i][j] = 0;
                continue;
            }

            // 그 외 경우 조사. 이웃한 곳들. 왼, 위, 대각선 왼쪽위, 세 곳을 조사해야한다.
            // [i][j-1], [i-1][j], [i-1][j-1]
            int mn = min(dp[i][j - 1], min(dp[i - 1][j], dp[i - 1][j - 1]));
            dp[i][j] = mn + 1;
            ans = max(ans, dp[i][j]);
        }
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            cout << dp[i][j] << " ";
        }
        cout << '\n';
    }

    cout << ans * ans << "\n";
    return 0;
}