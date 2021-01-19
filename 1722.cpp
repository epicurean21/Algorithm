#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

using namespace std;
#define MAX 201
#define ll long long
int N, K;
ll M, ans;
ll dp[MAX];
bool been[MAX];

// 팩토리얼
void factorial() {
    dp[0] = 1;
    for (int i = 1; i <= 20; i++)
        dp[i] = dp[i - 1] * i;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> K;
    factorial();
    if (K == 1) {
        cin >> M;
        vector<int> perm(N);
        for (int i = 0; i < N; i++) {
            for (int j = 1; j <= N; j++) {
                if (been[j]) continue;

                if (dp[N - i - 1] < M)
                    M -= dp[N - i - 1];
                else {
                    perm[i] = j;
                    been[j] = true;
                    break;
                }
            }
        }
        for (int i = 0; i < N; i++)
            cout << perm[i] << " ";
        cout << "\n";
    } else if (K == 2) {
        vector<int> perm(N);
        for (int i = 0; i < N; i++)
            cin >> perm[i];

        for (int i = 0; i < N; i++) {
            for (int j = 1; j < perm[i]; j++) {
                if (!been[j])
                    ans += dp[N - i - 1];
            }
            been[perm[i]] = true;
        }
        cout << ans + 1 << "\n";
    }
    return 0;
}