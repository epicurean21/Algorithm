/**
 * 10217 KCM Travel
 * 다익스트라, 그래프 이론, 다이나믹 프로그레밍
 *
 * 인천: 1번, LA: N번
 * 1 -> N 까지 M 원 이하이면서 최단경로
 * 각 지역별로 얼마남았는지를 계산하면서 최단경로를 찾으면 될듯?
 */
#include "iostream"
#include "vector"
#include "queue"

using namespace std;
#define ll long long
#define MAX 10001
int t, n, m, k, u, v, c, d;
string impossible = "Poor KCM\n";
vector<vector<pair<int, pair<int, int>>>> map; // from -> {to, {cost, dist}}
priority_queue<pair<pair<ll, ll>, int>, vector<pair<pair<ll, ll>, int>>, greater<>> pq; // total_dist, total_cost, next
ll dist[MAX];

void init() {
    map.clear();
    map.resize(n + 1);
    dist[1] = 0;
    for (int i = 2; i <= n; i++) dist[i] = INT64_MAX;
    while (!pq.empty()) pq.pop();
}

void dijkstra() {
    pq.push({{0, 0}, 1});
    while (!pq.empty()) {
        int cur = pq.top().second;
        ll cur_dist = pq.top().first.first;
        ll cur_cost = pq.top().first.second;
        pq.pop();

        if (dist[cur] < cur_dist) continue;
        if (cur_cost >= m) continue;

        for (int i = 0; i < map[cur].size(); i++) {
            int next = map[cur][i].first;
            ll next_dist = map[cur][i].second.second + cur_dist;
            ll next_cost = map[cur][i].second.first + cur_cost;

            if (dist[next] > next_dist || next_cost <= m) {
                dist[next] = next_dist;
                pq.push({{next_dist, next_cost}, next});
            }
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> t;
    while (t--) {
        cin >> n >> m >> k;

        init();
        while (k--) {
            cin >> u >> v >> c >> d;
            map[u].push_back({v, {c, d}});
        }

        dijkstra();
        if (dist[n] != INT64_MAX) cout << dist[n] << "\n";
        else cout << impossible;
    }

    return 0;
}