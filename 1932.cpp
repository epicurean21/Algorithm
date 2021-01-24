#include <iostream>

using namespace std;
#define MAX 501
int N;
int dp[MAX][MAX], map[MAX][MAX];

int max(int a, int b) {
    return a > b ? a : b;
}

void find() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < i + 1; j++) {
            if(i == 0) {
                dp[i][j] = map[i][j];
                continue;
            }
            if (j == 0)
                dp[i][j] = dp[i - 1][j] + map[i][j];
            else
                dp[i][j] = max(dp[i - 1][j] + map[i][j], dp[i - 1][j - 1] + map[i][j]);
        }
    }
    int tmp = 0;
    for (int i = 0; i < N; i++) {
        tmp = max(tmp, dp[N - 1][i]);
    }
    cout << tmp << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    for (int i = 1; i <= N; i++)
        for (int j = 0; j < i; j++)
            cin >> map[i - 1][j];

    find();

    return 0;
}