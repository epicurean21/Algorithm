/**
 * 1417 국회의원 선거
 * 자료구조, 우선순위 큐
 */
#include "bits/stdc++.h"

using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, v, cnt;
    cin >> n;
    priority_queue <pair<int, int >> votes;
    for (int i = 0; i < n; i++) {
        cin >> v;
        if (i == 0) cnt = v;
        votes.emplace(v, i + 1);
    }

    int ans = 0;
    while (votes.top().second != 1) {
        if(votes.top().first < cnt + ans) break;
        int c = votes.top().second;
        v = votes.top().first;

        votes.pop();

        votes.emplace(v - 1, c);
        ans++;
    }

    cout << ans << "\n";
    return 0;
}