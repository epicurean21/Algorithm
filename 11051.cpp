#include <iostream>
using namespace std;
#define MOD 10007
#define MAX 1001
#define ll long long
int N, K;
ll dp[MAX][MAX];
ll find(int N, int K) {
    for(int i = 2; i <= N; i++) {
        for(int j =0; j<= K; j++) {
            dp[i][j] = (dp[i-1][j-1] % MOD) + (dp[i-1][j] % MOD);
            dp[i][j] %= MOD;
        }
    }
    return dp[N][K];
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> K;
    dp[0][0] = 1;
    dp[1][0] = 1;
    dp[1][1] = 1;
    cout << find(N, K) << "\n";
    return 0;
}