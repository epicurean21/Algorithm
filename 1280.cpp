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
#define MAX 200001
#define ll long long
int N;
vector<ll> tree, dist;
vector<int> X, X_sum;

ll construct_tree(int node, int start, int end) {
    if (start == end)
        return tree[node] = X_sum[start];

    int m = (start + end) / 2;
    return (tree[node] = construct_tree(node * 2, start, m) % MOD) * (construct_tree(node * 2 + 1, m + 1, end) % MOD) %
           MOD;
}

void update(int node, int start, int end, int idx, int diff) {
    if (start == end) {
        tree[node] += diff;
        dist[node]++;
        return;
    }

    int m = (start + end) / 2;
    if (idx <= m)
        update(node * 2, start, m, idx, diff);
    else
        update(node * 2 + 1, m + 1, end, idx, diff);

    tree[node] = tree[node * 2] + tree[node * 2 + 1];
    dist[node] = dist[node * 2] + dist[node * 2 + 1];
}

ll sum(int node, int start, int end, int left, int right) {
    if (start > right || end < left)
        return 0;

    if (start >= left && end <= right)
        return dist[node];

    int m = (start + end) / 2;
    return (sum(node * 2, start, m, left, right) % MOD) * (sum(node * 2 + 1, m + 1, end, left, right) % MOD) % MOD;
}

ll query(int node, int start, int end, int left, int right) {
    if (start > right || end < left)
        return 0;

    if (start >= left && end <= right)
        return tree[node];

    int m = (start + end) / 2;
    return (query(node * 2, start, m, left, right) % MOD) * (query(node * 2 + 1, m + 1, end, left, right) % MOD) % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;

    X.resize(N + 1);

    int height = (ceil)(log2(N + 1));
    tree.resize(1 << (height + 1));
    dist.resize(1 << (height + 1));
    cin >> X[0];
    update(1, 0, MAX, X[0], X[0]);
    ll ans = 1;
    for (int i = 1; i < N; i++) {
        cin >> X[i];
        ll Lcnt = sum(1, 0, MAX, 0, X[i] - 1);
        ll Rcnt = sum(1, 0, MAX, X[i] + 1, MAX);
        ll Lsum = query(1, 0, MAX, 0, X[i] - 1);
        ll Rsum = query(1, 0, MAX, X[i] + 1, MAX);
        ll temp = (Rsum - Lsum) - (Rcnt - Lcnt) * X[i];
        temp %= MOD;
        ans *= temp;
        ans %= MOD;
        update(1, 0, MAX, X[i], X[i]);
    }

    cout << ans << '\n';
    
    return 0;
}