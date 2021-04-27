#include <iostream>
#include <vector>

using namespace std;
#define MAX 10001
int N, task_time[MAX], pre_count, pre_task, ans;
vector<vector<int>> tasks;
int dp[MAX];

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    tasks.resize(N + 1);
    for (int i = 1; i <= N; i++) {
        cin >> task_time[i] >> pre_count;
        dp[i] = task_time[i];
        for (int j = 0; j < pre_count; j++) {
            cin >> pre_task;
            tasks[i].push_back(pre_task);
        }
    }

    for (int i = 1; i <= N; i++) {
        int max_val = 0;
        for (int j = 0; j < tasks[i].size(); j++) {
            int pre = tasks[i][j];
            max_val = max(max_val, task_time[i] + dp[pre]);
        }
        dp[i] = max(dp[i], max_val);
    }

    for(int i = 1; i <= N; i++)
        ans = max(ans, dp[i]);

    cout << ans << '\n';
    return 0;
}