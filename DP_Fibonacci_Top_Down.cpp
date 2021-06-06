#include <iostream>

using namespace std;
#define MAX 1001
int input_value;
int dp[MAX];

int fibonacci(int n) {
    if (dp[n] != 0) return dp[n];
    if (n == 0) return 0;
    if (n == 1) return 1;
    return dp[n] = fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> input_value;
    fibonacci(input_value);
    cout << dp[input_value] << "\n";
    return 0;
}