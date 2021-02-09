/*
 * SW Expert Academy Problem # 11389
 * Difficulty: D6
 */
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
#define MOD 10000003
#define ll long long
int T, N, X, cnt;
vector<int> A;
vector<ll> tree;

ll construct_tree(int node, int start, int end) {
    if (start == end)
        return tree[node] = A[start];

    int m = (start + end) / 2;
    return tree[node] =
                   ((construct_tree(node * 2, start, m) % MOD)
                    *
                    (construct_tree(node * 2 + 1, m + 1, end) % MOD))
                   % MOD;
}

ll query(int node, int start, int end, int left, int right) {
    if (start > right || end < left)
        return 1;

    if (start >= left && end <= right)
        return tree[node];

    int m = (start + end) / 2;
    ll lt = query(node * 2, start, m, left, right) % MOD;
    ll rt = query(node * 2 + 1, m + 1, end, left, right) % MOD;
    return (lt * rt) % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> T;

    for (int t = 1; t <= T; t++) {
        A.clear();
        tree.clear();
        cnt = 0;
        cin >> N >> X;
        A.resize(N + 1);

        for (int i = 1; i <= N; i++)
            cin >> A[i];
        int h = (int) ceil(log2(N + 1));
        tree.resize(1 << (h + 1));
        construct_tree(1, 1, N);

        for (int i = 1; i <= N; i++) {
            for (int j = i; j <= N; j++) {
                int start = i;
                int end = j;
                int result = query(1, 1, N, start, end);
                if (result == X) cnt++;
                else if (result > X && X != 0)
                    break;
            }
        }
        cout << cnt << '\n';
    }
    return 0;
}