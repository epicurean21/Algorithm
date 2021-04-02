#include <iostream>
#include <queue>
#include <vector>

using namespace std;
#define MAX 1010
int N, M, u, v, d, p[MAX], school[MAX], ans;
vector<vector<pair<int, int>>> map;
priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;

int find(int a) {
    if (a == p[a])
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

    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        p[i] = i;
    }
    for (int i = 1; i <= N; i++) {
        char MW;
        cin >> MW;
        if (MW == 'M')
            school[i] = 0;
        else
            school[i] = 1;
    }
    for (int i = 0; i < M; i++) {
        cin >> u >> v >> d;
        pq.push({d, {u, v}});
    }

    int edgeCnt = 0;
    while (!pq.empty()) {
        int from = pq.top().second.first;
        int there = pq.top().second.second;
        int cost = pq.top().first;

        pq.pop();
        if (find(from) == find(there)) continue;
        if ((school[from] == 0 && school[there] == 1)
            || (school[from] == 1 && school[there] == 0)) {
            merge(from, there);
            edgeCnt++;
            ans += cost;
        }
    }
    if (edgeCnt != N - 1)
        cout << "-1\n";
    else
        cout << ans << '\n';
    return 0;
}