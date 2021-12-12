/**
 * 3584 가장 가까운 공통 조상
 * LCA, 그래프 이론, DFS
 */
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <cstring>

using namespace std;
#define MAX 10001
int T, N, A, B, ancestor[MAX][20], X, Y;
vector<vector<int>> tree;
int depth[MAX], p[MAX];
int max_level;

void init(int n) {
    tree.clear();
    tree.resize(n + 1);
    memset(depth, 0, sizeof(depth));
    memset(p, 0, sizeof(p));

    for (int i = 0; i <= n; i++)
        for (int j = 0; j < 20; j++)
            ancestor[i][j] = 0;
}

void dfs(int here, int parent) {
    depth[here] = depth[parent] + 1;
    ancestor[here][0] = parent;
    max_level = (int) floor(log2(MAX));

    for (int i = 1; i <= max_level; i++) {
        int tmp = ancestor[here][i - 1];
        ancestor[here][i] = ancestor[tmp][i - 1];
    }

    for (int i = 0; i < tree[here].size(); i++) {
        int there = tree[here][i];
        if (there != parent)
            dfs(there, here);
    }
}

int lca(int a, int b) {
    if (depth[a] != depth[b]) {
        if (depth[a] > depth[b])
            swap(a, b);

        for (int i = max_level; i >= 0; i--) {
            if (depth[a] <= depth[ancestor[b][i]])
                b = ancestor[b][i];
        }
    }

    int lca = a;
    if (a != b) {
        for (int i = max_level; i >= 0; i--) {
            if (ancestor[a][i] != ancestor[b][i]) {
                a = ancestor[a][i];
                b = ancestor[b][i];
            }
            lca = ancestor[a][i];
        }
    }

    return lca;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;
    while (T--) {
        cin >> N;
        init(N);
        for (int i = 0; i < N - 1; i++) {
            cin >> A >> B;
            tree[A].emplace_back(B);
            tree[B].emplace_back(A);
            p[B] = A;
        }
        int root = 0;
        for (int i = 1; i <= N; i++)
            if (p[i] == 0)
                root = i;

            depth[0] = -1;

            dfs(root, 0);

            cin >> X >> Y;

            cout << lca(X, Y) << '\n';
    }
    return 0;
}