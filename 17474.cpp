/**
 * 17474 수열과 쿼리 26 [다이아 2]
 *  세그먼트 트리, Lazy Propagation, 자료구로
 */
#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
#define ll long long
int N, M, P, L, R, X;
vector<pair<ll, ll>> tree, lazy;
vector<int> An;

ll construct_tree_sum(int node, int start, int end) {
    if (start == end)
        return tree[node].first = An[start];

    int m = (start + end) / 2;
    return tree[node].first = construct_tree_sum(node * 2, start, m)
                              + construct_tree_sum(node * 2 + 1, m + 1, end);
}

ll construct_tree_max(int node, int start, int end) {
    if (start == end)
        return tree[node].second = An[start];

    int m = (start + end) / 2;
    return tree[node].second = max(construct_tree_max(node * 2, start, m),
                                   construct_tree_max(node * 2 + 1, m + 1, end));
}

void update_lazy_sum(int node, int start, int end) {
    if (lazy[node].first == 0)
        return;

    tree[node].first += (end - start + 1) * lazy[node].first;

    if (start != end) {
        lazy[node * 2].first += lazy[node].first;
        lazy[node * 2 + 1].first += lazy[node].first;
    }

    lazy[node].first = 0;
}

void update_lazy_max(int node, int start, int end) {
    if (lazy[node].second == 0)
        return;

    tree[node].second += (end - start + 1) * lazy[node].second;

    if (start != end) {
        lazy[node * 2].second += lazy[node].second;
        lazy[node * 2 + 1].second += lazy[node].second;
    }

    lazy[node].second = 0;
}

void min_update(int node, int start, int end, int left, int right, int diff) {
    update_lazy_sum(node, start, end);
    update_lazy_max(node, start, end);

    if (start > right || end < left)
        return;

    if (start >= left && end <= right) {

    }
}

ll sum(int node, int start, int end, int left, int right) {
    if (start > right || end < left)
        return 0;

    if (start >= left && end <= right)
        return tree[node].first;

    int m = (start + end) / 2;
    return sum(node * 2, start, m, left, right) + sum(node * 2 + 1, m + 1, end, left, right);
}

ll _max(int node, int start, int end, int left, int right) {
    if (start > right || end < left)
        return 0;

    if (start >= left && end <= right)
        return tree[node].second;

    int m = (start + end) / 2;
    return max(_max(node * 2, start, m, left, right), _max(node * 2 + 1, m + 1, end, left, right));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    int height = (int) ceil(log2(N + 1));
    tree.resize(1 << (height + 1));
    lazy.resize(1 << (height + 1));
    An.resize(N + 1);
    for (int i = 1; i <= N; i++)
        cin >> An[i];

    construct_tree_sum(1, 1, N);
    construct_tree_max(1, 1, N);

    cin >> M;
    while (M--) {
        cin >> P;
        if (P == 1) { // min값 적용 X에
            cin >> L >> R >> X;
            min_update(1, 1, N, L, R, X);
        } else if (P == 2) {
            cin >> L >> R;
            cout << _max(1, 1, N, L, R) << '\n';
        } else if (P == 3) {
            cin >> L >> R;
            cout << sum(1, 1, N, L, R) << '\n';
        }
    }

    return 0;
}