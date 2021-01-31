#include <iostream>
#include <algorithm>

using namespace std;
#define MAX 500001
#define ll long long
int N, K, tmp;
pair<int, int> food[MAX];
ll dp[MAX], sum;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N;
    for (int i = 1; i <= N; i++)
        cin >> food[i].second >> food[i].first;
    sort(food + 1, food + N + 1);

    dp[N] = food[N].second;
    for (int i = N - 1; i > 0; i--) // 누적 합 구해놓기
        dp[i] = min((ll) food[i].second, dp[i + 1]);

    tmp = 2e9;
    for (int i = 1; i <= N; i++) {
        sum += food[i].first;
        if (food[i].second - food[i].first < tmp) {
            tmp = food[i].second - food[i].first;
            K = i;
        }
        cout << min(sum - food[K].first + food[K].second, sum - food[i].first + dp[i]) << '\n';
    }
    return 0;
}

/*
#include <stdio.h>
#include <algorithm>

#define fst first
#define snd second
using namespace std;
typedef pair<int, int> pii;

int n, k, mn[500001];
long long sum;
pii p[500001];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%d %d", &p[i].fst, &p[i].snd);

    sort(p, p + n, [](const pii &i, const pii &j) { return i.snd < j.snd; });

    mn[n] = 2e9;
    for (int i = n - 1; i >= 0; i--) mn[i] = min(p[i].fst, mn[i + 1]);
    for (int i = 0; i < n; i++) {
        if (p[k].snd - p[k].fst < p[i].snd - p[i].fst) k = i;
        sum += (long long) p[i].snd;
        printf("%lld\n", min(sum - p[k].snd + p[k].fst, sum - p[i].snd + mn[i]));
    }

    return 0;
}
*/
