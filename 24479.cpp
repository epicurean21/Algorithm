/**
 * 24479 알고리즘 수업 - 깊이 우선 탐색 1
 * 그래프 이론, DFS, Sorting
 */
#include "iostream"
#include "vector"
#include "algorithm"

using namespace std;

int n, m, r, u, v, cnt = 1;
vector<vector<int>> map;
vector<int> order;

void dfs(int cur) {
    order[cur] = cnt;
    for (int next: map[cur]) {
        if (order[next] == 0) {
            cnt++;
            dfs(next);
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m >> r;
    map.resize(n + 1);
    order.resize(n + 1);

    for (int i = 0; i < m; i++) {
        cin >> u >> v;
        map[u].emplace_back(v);
        map[v].emplace_back(u);
    }

    for (int i = 1; i <= n; i++) sort(map[i].begin(), map[i].end());
    dfs(r);
    for (int i = 1; i <= n; i++) cout << order[i] << "\n";
}