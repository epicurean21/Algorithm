#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
#define MAX 100001
#define INF 9999999999
#define ll long long
int N, Q, x, y, a, b;
vector<int> node;
vector<ll> tree;

ll construct_tree(int idx, int start, int end) {
    if (start == end)
        return tree[idx] = node[start];

    int m = (start + end) / 2;
    return tree[idx] = construct_tree(idx * 2, start, m) + construct_tree(idx * 2 + 1, m + 1, end);
}

ll query(int idx, int start, int end, int left, int right) {
    if (start > right || end < left)
        return 0;

    if (start >= left && end <= right)
        return tree[idx];

    int m = (start + end) / 2;
    return query(idx * 2, start, m, left, right) + query(idx * 2 + 1, m + 1, end, left, right);
}

ll update(int idx, int Node, int value, int start, int end) {
    if (idx < start || end < idx)
        return tree[Node];

    if (start == end)
        return tree[Node] = value;

    int m = (start + end) / 2;
    return tree[Node] = update(idx, Node * 2, value, start, m) + update(idx, Node * 2 + 1, value, m + 1, end);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N >> Q;
    node.resize(N + 1);
    int h = (int) (ceil(log2(N)));
    tree.resize(1 << h + 1);
    for (int i = 1; i <= N; i++)
        cin >> node[i];
    construct_tree(1, 1, N);
    for (int i = 0; i < Q; i++) {
        cin >> x >> y >> a >> b;
        if (x > y)
            swap(x, y);
        cout << query(1, 1, N, x, y) << '\n';
        update(a, 1, b, 1, N);
    }
    return 0;
}