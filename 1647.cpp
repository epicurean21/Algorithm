#include <iostream>
#include <vector>
#include <queue>

using namespace std;
#define MAX 100001
int N, M, A, B, C, ans, maxCost;
int p[MAX];
priority_queue<pair<int, pair<int, int>>,
        vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;

int max(int a, int b) {
    return a > b ? a : b;
}

int find(int a) {
    if (p[a] == a)
        return a;
    return p[a] = find(p[a]);
}

void merge(int a, int b) {
    int aa = find(a);
    int bb = find(b);
    if (aa == bb) return;

    p[aa] = bb;
}

void init() {
    for (int i = 1; i <= N; i++)
        p[i] = i;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N >> M;
    init();
    for (int i = 0; i < M; i++) {
        cin >> A >> B >> C;
        pq.push({C, {A, B}});
    }
    while (!pq.empty()) {
        int from = pq.top().second.first;
        int there = pq.top().second.second;
        int cost = pq.top().first;
        pq.pop();

        if (find(from) == find(there)) continue;
        merge(from, there);
        ans += cost;
        maxCost = max(cost, maxCost);
    }

    cout << ans - maxCost << '\n';
    return 0;
}