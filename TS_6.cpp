#include <string>
#include <vector>
#include <iostream>

using namespace std;

long long solution(int numOfStairs) {
    long long answer = 0;
    long long dp[71];
    dp[1] = 1;
    dp[2] = 2;
    dp[3] = 4;
    for (int i = 4; i <= numOfStairs; i++) {
        dp[i] = dp[i - 1] + dp[i - 2] + dp[i - 3];
    }
    answer = dp[numOfStairs];
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    long long dp[71];
    dp[1] = 1;
    dp[2] = 2;
    dp[3] = 4;
    for (int i = 4; i <= 70; i++) {
        dp[i] = dp[i - 1] + dp[i - 2] + dp[i - 3];
    }
    cout << dp[70] << '\n';
    return 0;
}