#include <iostream>
#include <vector>
#include <queue>

using namespace std;
#define MAX 505
int N, P;
int constructTime[MAX], inDegree[MAX], ans[MAX];
vector<vector<int>> tree(MAX);
queue<int> q;
bool visited[MAX];

int max(int a, int b) {
    return a > b ? a : b;
}

void dfs() {
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        for (int i = 0; i < tree[cur].size(); i++) {
            int next = tree[cur][i];
            ans[next] = max(ans[next], ans[cur] + constructTime[cur]);
            inDegree[next]--;
            if (!inDegree[next])
                q.push(next);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    for (int i = 1; i <= N; i++) {
        int time;
        cin >> time;
        constructTime[i] = time;
        while (cin >> P) {
            if (P == -1) break;
            inDegree[i]++;
            tree[P].push_back(i);
        }
    }

    for (int i = 1; i <= N; i++)
        if (!inDegree[i])
            q.push(i);
    dfs();

    for (int i = 1; i <= N; i++)
        cout << ans[i] + constructTime[i] << "\n";
    return 0;
}