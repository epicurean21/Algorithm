#include <iostream>
#include <vector>

using namespace std;
#define MAX 1001
int N, A[MAX], dp[MAX];
vector<int> LIS[MAX], ans;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    for (int i = 1; i <= N; i++)
        cin >> A[i];

    for (int i = 1; i <= N; i++) {
        dp[i] = 1;
        LIS[i].push_back(A[i]);
        for (int j = 1; j < i; j++) {
            if (A[i] > A[j]) {
                if (dp[i] < dp[j] + 1) {
                    LIS[i].clear();
                    LIS[i] = LIS[j];
                    LIS[i].push_back(A[i]);
                    dp[i] = dp[j] + 1;
                }
            }
        }
        if (ans.size() < LIS[i].size())
            ans = LIS[i];
    }
    cout << ans.size() << '\n';
    for (int i = 0; i < ans.size(); i++)
        cout << ans[i] << " ";
    cout << '\n';
    return 0;
}