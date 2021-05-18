#include <iostream>
#include <vector>

using namespace std;
#define MAX 100001
vector<vector<int>> map;
vector<int> ans;
int N, a, b;
int depth[MAX];

void dfs(int cur, int d) {
    if (depth[cur]) return;
    depth[cur] = d;

    for (int i = 0; i < map[cur].size(); i++) {
        int next = map[cur][i];
        if (depth[next]) continue;
        dfs(next, d + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N;
    map.resize(N + 1);
    ans.resize(N);
    for (int i = 0; i < N - 1; i++) {
        cin >> a >> b;
        map[a].push_back(b);
        map[b].push_back(a);
    }
    for (int i = 0; i < N; i++)
        cin >> ans[i];

    dfs(1, 1);
    for (int i = 0; i < N; i++)
        if (depth[ans[i]] != i + 1)
            cout << "0\n";
    cout << "1\n";
    return 0;
}