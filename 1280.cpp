/**
 * Segment Tree
 * i번째 나무 심는 cost = 1 ~ (i-1) 까지의 거리의 합 --> 구간합
 * 문제의 정답: 2~N번 나무까지 심는 cost의 곱
 *
 * 즉 i번째 나무의 cost를 구해놓고
 * segment tree는 구간 곱?
 */

#include <iostream>
#include <vector>

using namespace std;
#define MOD 1000000007
#define ll long long
int N;
vector<ll> tree;
vector<int> X, X_sum;

ll construct_tree(int node, int start, int end) {
    if (start == end)
        return tree[node] = X_sum[start];

    int m = (start + end) / 2;
    return tree[node] = construct_tree(node * 2, start, m);
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
            X_sum[i] = X_sum[i - 1] + X[i] - X[1];
    }

    return 0;
}