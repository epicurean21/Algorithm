#include <iostream>
#include <algorithm>
#include <string>

using namespace std;
#define INF 1000000000
#define MAX 201
int N, M, K, a, z;
int dp[MAX][MAX];
string ans;

// 필요한 부분만 파스칼 삼각형을 만들자 !
int pascal(int n, int r) {
    // r == 0, n == r -> 1
    // dp[n][r] = dp[n-1][r-1] + dp[n-1][r]

    if (n == r || r == 0)
        return 1;
    else if (dp[n][r])
        return dp[n][r];
    else
        return dp[n][r] = min(INF, pascal(n - 1, r - 1) + pascal(n - 1, r));
}

void solve(int n, int m, int k) {
    // n == 0 && m == 0
    if (n + m == 0)
        return;
    // n == 0
    // m == 0
    if (n == 0) {
        ans += 'z';
        solve(n, m - 1, k);
    } else if (m == 0) {
        ans += 'a';
        solve(n - 1, m, k);
    } else {
        int leftCount = pascal(n + m - 1, m); // a 를 하나 고르고 z 개수는 그대로인 combination
        if (leftCount >= k) {
            ans += 'a';
            solve(n - 1, m, k);
        } else {
            ans += 'z';
            solve(n, m - 1, k - leftCount);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M >> K;
    if (K > pascal(N + M, M))
        cout << "-1\n";
    else {
        solve(N, M, K);
        cout << ans << "\n";
    }
    return 0;
}