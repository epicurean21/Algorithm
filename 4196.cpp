#include <iostream>
#include <stack>
#include <vector>
#include <cstring>

#define MAX 100001
using namespace std;
int T, N, M, x, y;

stack<int> finished_stack;
vector<vector<int>> g;
vector<vector<int>> gt;
bool visited[MAX];

void init() {
    g.clear();
    gt.clear();
    memset(visited, false, sizeof(visited));
}

void dfs(int cur) {
    if (visited[cur])
        return;
    visited[cur] = true;
    for (int i = 0; i < g[cur].size(); i++) {
        if (!visited[g[cur][i]])
            dfs(g[cur][i]);
    }
    finished_stack.push(cur);
}

void dfs2(int cur) {
    if (visited[cur])
        return;
    visited[cur] = true;
    for (int i = 0; i < gt[cur].size(); i++) {
        if (!visited[gt[cur][i]])
            dfs(gt[cur][i]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> T;
    while (T--) {
        cin >> N >> M;
        init();
        g.resize(N + 1);
        gt.resize(N + 1);
        for (int i = 0; i < M; i++) {
            cin >> x >> y;
            g[x].emplace_back(y);
            gt[y].emplace_back(x);
        }

        for (int i = 1; i <= N; i++) {
            if (!visited[i])
                dfs(i);
        }
        memset(visited, false, sizeof(visited));

        int cnt = 0;
        while (!finished_stack.empty()) {
            if (!visited[finished_stack.top()]) {
                dfs2(finished_stack.top());
                cnt++;
            }
            finished_stack.pop();
        }

        cout << cnt << "\n";
    }
    return 0;
}