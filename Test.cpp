/**
 * 13547 수열과 쿼리 5 [플래티넘 2]
 * 오프라인 쿼리 & mo's
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;
#define MAX 1000001
int N, M, A[MAX], table[MAX], X, Y, sqrt_value;
vector<pair<int, pair<int, int>>> query;
vector<int> res;

bool cmp(pair<int, pair<int, int>> &x, pair<int, pair<int, int>> &y) {
    if (x.second.first / sqrt_value != y.second.first / sqrt_value)
        return x.second.first / sqrt_value < y.second.first / sqrt_value;
    return x.second.second < y.second.second;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    sqrt_value = sqrt(N);
    for (int i = 0; i < N; i++)
        cin >> A[i];
    cin >> M;
    query.resize(M + 1);
    res.resize(M + 1);

    for (int i = 0; i < M; i++) {
        cin >> X >> Y;
        query[i] = {i, {X - 1, Y - 1}};
    }

    sort(query.begin(), query.end(), cmp);

    int ans = 0;
    int s = query[0].second.first, e = query[0].second.second;
    for (int a = s; a <= e; a++) {
        if (table[A[a]] == 0)
            ans++;
        table[A[a]]++;
    }

    res[query[0].first] = ans;

    for (int a = 1; a < M; a++) {
        while (query[a].second.first < s) {
            if (table[A[--s]] == 0)
                ans++;
            table[A[s]]++;
        }
        while (query[a].second.second > e) {
            if (table[A[++e]] == 0)
                ans++;
            table[A[e]]++;
        }
        while (query[a].second.first > s) {
            table[A[s]]--;
            if (table[A[s++]] == 0)
                ans--;
        }
        while (query[a].second.second < e) {
            table[A[e]]--;
            if (table[A[e--]] == 0)
                ans--;
        }

        res[query[a].first] = ans;
    }

    for (int i = 0; i < M; i++)
        cout << res[i] << '\n';

    return 0;
}