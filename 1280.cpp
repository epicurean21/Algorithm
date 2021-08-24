/**
 * Segment Tree
 * i번째 나무 심는 cost = 1 ~ (i-1) 까지의 거리의 합 --> 구간합
 * - 근데 이게 오름차순 일 필요없음. 좌표에 따른 거리 값.
 * 문제의 정답: 2~N번 나무까지 심는 cost의 곱
 *
 * 즉 i번째 나무의 cost를 구해놓고
 * segment tree는 구간 곱?
 *
 * segment tree로 좌표에 따른 각 위치의 cost를 구하고,
 * 그 값들을 이용해 또 다른 구간 곱 세그먼트 트리를 구성
 */

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
#define MOD 1000000007
#define ll long long
int N;
vector<ll> tree;
vector<ll> distance;
vector<int> X, X_sum;

ll construct_tree(int node, int start, int end) {
    if (start == end)
        return tree[node] = X_sum[start];

    int m = (start + end) / 2;
    return (tree[node] = construct_tree(node * 2, start, m) % MOD) * (construct_tree(node * 2 + 1, m + 1, end) % MOD) %
           MOD;
}

ll sum(int node, int start, int end, int left, int right) {
    if (start > right || end < left)
        return 0;

    if (start >= left && end <= right)
        return tree[node];

    int m = (start + end) / 2;

//    return (sum(node * 2, start, m, left, right) % MOD) +
}

ll query(int node, int start, int end, int left, int right) {
    if (start > right || end < left)
        return 1;

    if (start >= left && end <= right) {
        return tree[node];
    }

    int m = (start + end) / 2;
    return (query(node * 2, start, m, left, right) % MOD) * (query(node * 2 + 1, m + 1, end, left, right) % MOD) % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;

    X.resize(N + 1);
    X_sum.resize(N + 1);
    X_sum[1] = 0;

    int height = (ceil)(log2(N + 1));
    tree.resize(1 << (height + 1));

    for (int i = 1; i <= N; i++) {
        cin >> X[i];
        if (i >= 2)
            X_sum[i] = X_sum[i - 1] + abs(X[i] - X[1]);
    }

    construct_tree(1, 1, N);

    cout << query(1, 1, N, 2, N) % MOD << '\n';
    return 0;
}