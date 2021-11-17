/**
 * 14938 서강그라운드: Dijkstra, Floyd-Warshall
 * 그냥 다익스트라..
 */
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
int n, m, r, a, b, l, ans;
vector<int> item_count, dist;
vector<bool> chk;
vector<vector<pair<int, int>>> map;
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

void init() {
    item_count.resize(n + 1);
    chk.resize(n + 1);
    map.resize(n + 1);
    dist.resize(n + 1, INT32_MAX);
}

void reset() {
    for (int i = 0; i <= n; i++) {
        dist[i] = INT32_MAX;
        chk[i] = false;
    }
}

int dijkstra(int s, int c) {
    dist[s] = 0;
    pq.push({c, s});
    chk[s] = true;
    int possible_value = item_count[s];

    while (!pq.empty()) {
        int cur = pq.top().second;
        int cost = pq.top().first;
        pq.pop();

        if (dist[cur] < cost) continue;

        for (int i = 0; i < map[cur].size(); i++) {
            int next = map[cur][i].first;
            int next_cost = map[cur][i].second + cost;
            if (next_cost > m) continue;

            if (dist[next] > next_cost) {
                dist[next] = next_cost;
                if (!chk[next]) {
                    possible_value += item_count[next];
                    chk[next] = true;
                }
                pq.push({next_cost, next});
            }
        }
    }

    return possible_value;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m >> r;

    init();

    for (int i = 1; i <= n; i++)
        cin >> item_count[i];
    for (int i = 0; i < r; i++) {
        cin >> a >> b >> l;
        map[a].emplace_back(b, l);
        map[b].emplace_back(a, l);
    }

    for (int i = 1; i <= n; i++) {
        reset();
        ans = max(ans, dijkstra(i, 0));
    }

    cout << ans << '\n';

    return 0;
}