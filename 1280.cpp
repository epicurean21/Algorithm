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
#define MAX 200000
#define SIZE 262144
#define ll long long

int N;
vector<ll> tree(MAX * 4 + 1), dist(MAX * 4 + 1);
vector<int> X;

void update(int idx, int val) {
    idx += SIZE;
    dist[idx] += val;
    tree[idx]++;

    while (idx > 1) {
        idx /= 2;
        dist[idx] = dist[2 * idx] + dist[2 * idx + 1];
        tree[idx] = tree[2 * idx] + tree[2 * idx + 1];
    }
}

ll sumQuery(int L, int R, int nodeIdx, int nodeL, int nodeR) {
    if (R < nodeL || nodeR < L)
        return 0;

    if (L <= nodeL && nodeR <= R)
        return dist[nodeIdx];

    int m = (nodeL + nodeR) / 2;

    return sumQuery(L, R, 2 * nodeIdx, nodeL, m) + sumQuery(L, R, 2 * nodeIdx + 1, m + 1, nodeR);
}

ll cntQuery(int L, int R, int nodeIdx, int nodeL, int nodeR) {
    if (R < nodeL || nodeR < L)
        return 0;

    if (L <= nodeL && nodeR <= R)
        return tree[nodeIdx];

    int m = (nodeL + nodeR) / 2;

    return cntQuery(L, R, 2 * nodeIdx, nodeL, m) + cntQuery(L, R, 2 * nodeIdx + 1, m + 1, nodeR);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;

    X.resize(N + 2);

    cin >> X[0];
    update(X[0], X[0]);
    ll ans = 1;
    for (int i = 1; i < N; i++) {
        cin >> X[i];
        ll left = cntQuery(0, X[i], 1, 0, SIZE) * X[i] - sumQuery(0, X[i], 1, 0, SIZE);
        ll right = sumQuery(X[i] + 1, MAX, 1, 0, SIZE) - cntQuery(X[i] + 1, MAX, 1, 0, SIZE) * X[i];
        ans = (left + right) % MOD * ans % MOD;
        update(X[i], X[i]);
    }

    cout << ans << '\n';

    return 0;
}