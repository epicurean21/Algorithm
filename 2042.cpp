#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
#define MAX 1000001
#define ll long long
int N, M, K, a, b;
ll A[MAX], c;
vector<ll> tree;

ll construct_tree(int node, int start, int end) { // indexed tree construction
    if (start == end)
        return tree[node] = A[start];

    int m = (start + end) / 2;
    return tree[node] = construct_tree(node * 2, start, m) + construct_tree(node * 2 + 1, m + 1, end);
}

ll query(int node, int start, int end, int left, int right) { // 구간 합 Query 문 수행
    if (start > right || end < left)
        return 0;

    if (start >= left && end <= right)
        return tree[node];

    int m = (start + end) / 2;
    return query(node * 2, start, m, left, right) + query(node * 2 + 1, m + 1, end, left, right);
}

void update(int node, int start, int end, int idx, ll diff) {
    if (start <= idx && idx <= end)
        tree[node] += diff;
    else
        return;
    if (start == end) return;

    int m = (start + end) / 2;
    update(node * 2, start, m, idx, diff);
    update(node * 2 + 1, m + 1, end, idx, diff);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M >> K;
    for (int i = 1; i <= N; i++)
        cin >> A[i];

    int height = (int) ceil(log2(N + 1));
    tree.resize(1 << height + 1);

    construct_tree(1, 1, N);
    for (int i = 0; i < M + K; i++) {
        cin >> a >> b >> c;
        if (a == 1) { // 구간 바꾸기
            ll diff = c - A[b];
            A[b] = c;
            update(1, 1, N, b, diff);
        } else if (a == 2) { // 구간 합 구하기
            cout << query(1, 1, N, b, c) << '\n';
        }
    }
    return 0;
}