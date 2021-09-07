#include<iostream>
#include<vector>

using namespace std;
typedef long long ll;
const int MOD = 1000000007;
const int END = 200000;
const int SIZE = 262144;
int N, segSize = SIZE;
vector<ll> sum, cnt;

void update(int idx, int val) {
    idx += segSize;
    sum[idx] += val;
    cnt[idx]++;
    while (idx > 1) {
        idx /= 2;
        sum[idx] = sum[2 * idx] + sum[2 * idx + 1];
        cnt[idx] = cnt[2 * idx] + cnt[2 * idx + 1];
    }
}

ll sumQuery(int L, int R, int nodeIdx, int nodeL, int nodeR) {
    if (R < nodeL || nodeR < L) return 0;
    if (L <= nodeL && nodeR <= R) return sum[nodeIdx];
    int mid = (nodeL + nodeR) / 2;
    return sumQuery(L, R, 2 * nodeIdx, nodeL, mid) + sumQuery(L, R, 2 * nodeIdx + 1, mid + 1, nodeR);
}

ll cntQuery(int L, int R, int nodeIdx, int nodeL, int nodeR) {
    if (R < nodeL || nodeR < L) return 0;
    if (L <= nodeL && nodeR <= R) return cnt[nodeIdx];
    int mid = (nodeL + nodeR) / 2;
    return cntQuery(L, R, 2 * nodeIdx, nodeL, mid) + cntQuery(L, R, 2 * nodeIdx + 1, mid + 1, nodeR);
}

int main() {
    int x;
    ll ans = 1;
    scanf("%d%d", &N, &x);
    sum.resize(2 * segSize, 0);
    cnt.resize(2 * segSize, 0);
    update(x, x);
    for (int i = 1; i < N; i++) {
        scanf("%d", &x);
        ll left = cntQuery(0, x, 1, 0, SIZE) * x - sumQuery(0, x, 1, 0, SIZE);
        ll right = sumQuery(x + 1, END, 1, 0, SIZE) - cntQuery(x + 1, END, 1, 0, SIZE) * x;
        ans = (left + right) % MOD * ans % MOD;
        update(x, x);
    }
    printf("%lld\n", ans);
    return 0;
}