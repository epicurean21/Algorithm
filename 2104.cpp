/**
 * 2104 부분배열 고르기
 * 세그먼트 트, 분할정복, 스택
 */

#include <iostream>
#include <stack>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
#define ll long long
int N;
vector<int> tree_min, A;
vector<ll> tree_sum;


int cal_index(int a, int b) {
    if (a == -1)
        return b;
    if (b == -1)
        return a;
    if (A[a] < A[b]) return a;
    return b;
}

int min_value(int node, int start, int end, int left, int right) {
    if (start > right || end < left) return INT32_MAX;

    if (start >= left && end <= right)
        return tree_min[node];

    int m = (start + end) / 2;
    return cal_index(min_value(node * 2, start, m, left, right), min_value(node * 2 + 1, m + 1, end, left, right));
}

ll sum_value(int node, int start, int end, int left, int right) {
    if (start > right || end < left)
        return 0;

    if (start >= left && end <= right)
        return tree_sum[node];

    int m = (start + end) / 2;
    return sum_value(node * 2, start, m, left, right) + sum_value(node * 2 + 1, m + 1, end, left, right);
}

ll construct_tree_sum(int node, int start, int end) {
    if (start == end)
        return tree_sum[node] = (ll) A[start];

    int m = (start + end) / 2;

    return tree_sum[node] = construct_tree_sum(node * 2, start, m) + construct_tree_sum(node * 2 + 1, m + 1, end);
}

int construct_tree_min(int node, int start, int end) {
    if (start == end)
        return tree_min[node] = A[start];
    int m = (start + end) / 2;
    return tree_min[node] = cal_index(construct_tree_min(node * 2, start, m),
                                      construct_tree_min(node * 2 + 1, m + 1, end));
}

ll query(int start, int end) {
    if (start == end)
        return tree_sum[start] * tree_min[start];
    int idx = min_value(1, 1, N, start, end);
    ll ans = A[idx] * sum_value(1, 1, N, start, end);
    if (start < idx)
        ans = max(ans, query(start, idx - 1));
    if (idx < end)
        ans = max(ans, query(idx + 1, end));

    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    int h = (int) ceil(log2(N + 1));
    A.resize(N + 1);
    tree_sum.resize(1 << (h + 1));
    tree_min.resize(1 << (h + 1));

    for (int i = 1; i <= N; i++)
        cin >> A[i];

    construct_tree_min(1, 1, N);
    construct_tree_sum(1, 1, N);

    cout << query(1, N) << '\n';
    return 0;
}