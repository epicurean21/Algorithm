/**
 * 13511 트리와 쿼리 2 [플레티넘 2]
 * LCA, 공통조상찾기
 * 어렵네.. 해결못했음
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define MAX 100001
#define ll long long
int N, M, u, v, w, k, q;
int depth[MAX], ancestor[MAX][20], p[MAX];
ll cost_tree[MAX][20];
bool visited[MAX];
vector<vector<pair<int, int>>> tree(MAX);

void dfs(int p, int c, int dep, int cost) {
    if (visited[c]) return;
    visited[c] = true;
    depth[c] = dep;
    ancestor[c][0] = p;
    cost_tree[c][0] = cost;
    for (int i = 0; i < tree[c].size(); i++) {
        dfs(c, tree[c][i].first, dep + 1, tree[c][i].second);
    }
}

ll query_one_lca(int a, int b) {
    ll cost = 0;
    if (depth[a] < depth[b]) {
        swap(a, b);
    }

    if (depth[a] != depth[b]) {
        int diff = depth[a] - depth[b];
        for (int i = 19; i >= 0; i--) {
            if (diff >= (1 << i)) {
                cost += cost_tree[a][i];
                a = ancestor[a][i];
            }
        }
    }

    if (a == b)
        return cost;

    for (int i = 19; i >= 0; i--) {
        if (ancestor[a][i] != ancestor[b][i]) {
            cost += cost_tree[a][i];
            a = ancestor[a][i];
            cost += cost_tree[b][i];
            b = ancestor[b][i];
        }
    }

    return cost + cost_tree[a][0] + cost_tree[b][0];
}

int query_two_lca(int a, int b, int c) {
    if (depth[a] < depth[b]) {
        swap(a, b);
    }

    if (depth[a] != depth[b]) {
        int diff = depth[a] - depth[b];
        for (int i = 19; i >= 0; i--) {
            if (diff >= (1 << i)) {
                a = ancestor[a][i];
            }
        }
    }

    if (a != b) {
        for (int i = 19; i >= 0; i--) {
            if (ancestor[a][i] != ancestor[b][i]) {
                a = ancestor[a][i];
                b = ancestor[b][i];
            }
        }
    }

    return ancestor[a][0];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    for (int i = 0; i < N - 1; i++) {
        cin >> u >> v >> w;
        tree[u].emplace_back(v, w);
        tree[v].emplace_back(u, w);
        p[v] = u;
    }

    int root = -1;
    for (int i = 1; i <= N; i++) {
        if (p[i] == 0) {
            root = i;
            break;
        }
    }

    dfs(0, root, 0, 0);
    cin >> M;
    while (M--) {
        cin >> q >> u >> v;
        if (q == 1) {
            cout << query_one_lca(u, v) << '\n';
        } else if (q == 2) {
            cin >> k;
            int p = query_two_lca(u, v, k);
            if (depth[u] - depth[v] + 1 >= k) {
                int diff = k - 1;
                int cur = u;

                for (int i = 0; diff != 0; ++i) {
                    if (diff % 2 == 1)
                        cur = ancestor[cur][i];
                    diff = diff >> 1;
                }

                cout << cur << '\n';
            } else {
                k = k - (depth[u] - depth[p]);

                int diff = depth[v] - depth[p] + 1 - k;
                int cur = v;

                for (int i = 0; diff != 0; ++i) {
                    if (diff % 2 == 1)
                        cur = ancestor[cur][i];
                    diff = diff >> 1;
                }

                cout << cur << '\n';
            }
        }
    }

    return 0;
}