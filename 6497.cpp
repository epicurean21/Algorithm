#include <iostream>
#include <queue>

using namespace std;
#define MAX 200001
int m, n, x, y, z, p[MAX], totalCost, cnt;
priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;

void init() {
    totalCost = 0;
    cnt = 0;
    for (int i = 0; i < m; i++)
        p[i] = i;
    while (!pq.empty()) pq.pop();
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
    p[bb] = aa;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    while (cin >> m >> n) {
        if (m == 0 && n == 0) break;
        init();

        for (int i = 0; i < n; i++) {
            cin >> x >> y >> z;
            totalCost += z;
            pq.push({z, {x, y}});
        }

        while (!pq.empty()) {
            int from = pq.top().second.first;
            int there = pq.top().second.second;
            int cost = pq.top().first;
            pq.pop();
            int pf = find(from);
            int pt = find(there);
            if (pf == pt) continue;
            merge(pf, pt);
            cnt++;
            totalCost -= cost;
            if (cnt == n) break;
        }
        cout << totalCost << '\n';
    }
    return 0;
}