/**
 * 23843 콘센트
 * 자료구조, 우선순위 큐, 그리디 알고리즘
 */

#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>

using namespace std;
int N, M, t, ans, tmp;
priority_queue<int, vector<int>, greater<>> pq;
vector<int> n;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        cin >> t;
        n.emplace_back(t);
    }
    sort(n.begin(), n.end(), greater<>());

    if (M == 1) {
        for (int i = 0; i < N; i++)
            ans += n[i];
    } else if (N < M) {
        ans += n[0];
    } else {
        tmp += M;
        for (int i = 0; i < M; i++)
            pq.push(n[i]);

        while (tmp < N) {
            int top_value = pq.top();
            pq.pop();
            while (top_value <= pq.top() && tmp < N) {
                top_value += n[tmp];
                tmp++;
            }
            pq.push(top_value);
        }
        for (int i = 0; i < M - 1; i++)
            pq.pop();
        ans = pq.top();
    }

    cout << ans << '\n';

    return 0;
}