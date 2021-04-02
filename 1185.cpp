#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;
#define MAX 10010
int N, P, C[MAX], S, E, L, p[MAX], ans;
priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;

int find(int a) {
    if (p[a] == a)
        return a;
    return p[a] = find(p[a]);
}

void merge(int a, int b) {
    int aa = find(a);
    int bb = find(b);
    p[aa] = bb;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> P;
    for (int i = 1; i <= N; i++)
        p[i] = i;
    for (int i = 1; i <= N; i++)
        cin >> C[i]; // 나라 방문 비용
    for (int i = 0; i < P; i++) { // 도로 비용
        cin >> S >> E >> L;
        int cost = L * 2 + C[S] + C[E];
        pq.push({cost, {S, E}});
    }
    sort(C, C + N + 1);
    while (!pq.empty()) {
        int from = pq.top().second.first;
        int there = pq.top().second.second;
        int cost = pq.top().first;
        pq.pop();
        if (find(from) == find(there))
            continue;
        merge(from, there);
        ans += cost;
    }
    cout << ans + C[1] << '\n';
    return 0;
}