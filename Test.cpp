#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;
#define MAX 100001
int n, m, p, q;
int A[MAX], cnt[MAX * 10], query[MAX];
struct Query {
    int idx, s, e;
} Q[MAX];
int sq;

bool cmp(Query u, Query v) {
    if (u.s / sq == v.s / sq) return u.e < v.e;
    return u.s / sq < v.s / sq;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    sq = sqrt(n);
    for (int i = 0; i < n; i++) cin >> A[i];
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> p >> q;
        Q[i] = {i, p - 1, q - 1};
    }
    sort(Q, Q + m, cmp);
    int ret = 0;
    int st = Q[0].s;
    int ed = Q[0].e;
    for (int i = st; i <= ed; i++) {
        if (cnt[A[i]]++ == 0) ret++;
    }
    query[Q[0].idx] = ret;

    for (int i = 1; i < m; i++) {
        while (Q[i].s < st) {
            if (cnt[A[--st]]++ == 0)
                ret++;
        }

        while (Q[i].e > ed) {
            if (cnt[A[++ed]]++ == 0)
                ret++;
        }

        while (Q[i].s > st) {
            if (--cnt[A[st++]] == 0) ret--;
        }

        while (Q[i].e < ed) {
            if (--cnt[A[ed--]] == 0) ret--;
        }

        query[Q[i].idx] = ret;
    }
    for (int i = 0; i < m; i++) {
        cout << query[i] << '\n';
    }
}