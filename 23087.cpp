/**
 * 23089 최단최단경로 [골드2]
 * 다익스트라 그래프 이론
 * dist[] 배열에 목적지까지의 경로를 저장하고
 * trasnfer_count 는 pair로 최단경로이면서 최소환승에 대한 {환승 수, 해당경로 개수} 를 저장했습니다.
 * 따끔한 지적 및 반례 부탁드립니다. 감사합니다
 * 해결 못했슴..
 */

#include <iostream>
#include <vector>
#include <queue>

using namespace std;
#define MAX 100001
#define ll long long
#define MOD 1000000009
int N, M, X, Y, u, v, w;
ll dist[MAX];
pair<ll, ll> transfer_count[MAX]; // 최단경로이면서 최소 환승
vector<vector<pair<int, int>>> map;

void init() {
    for (int i = 0; i <= N; i++) {
        dist[i] = INT64_MAX;
        transfer_count[i].first = INT64_MAX;
        transfer_count[i].second = 0;
    }
}

void dijkstra() {
    priority_queue<pair<pair<ll, ll>, int>, vector<pair<pair<ll, ll>, int>>, greater<>> pq;
    pq.push({{0, 0}, X});
    dist[X] = 0;
    transfer_count[X].first = 0;
    while (!pq.empty()) {
        int cur = pq.top().second;
        ll cost = pq.top().first.first;
        ll transfer = pq.top().first.second;
        pq.pop();
        if (dist[cur] < cost) continue;
        if (transfer_count[cur].first < transfer) continue;

        for (auto &i : map[cur]) {
            int next = i.first;
            ll next_cost = i.second + cost;

            // 거리가 같거나 작으면서 환승 수가 기존보다 크거나 같으면
            if (next_cost <= dist[next] && (transfer + 1) <= transfer_count[next].first) {
                if (transfer_count[next].first == INT64_MAX) { // 최초 도달
                    transfer_count[next].first = (transfer + 1) % MOD;
                    transfer_count[next].second = 1;
                    dist[next] = next_cost;
                    pq.push({{next_cost, transfer + 1}, next});
                } else if (dist[next] < next_cost && transfer_count[next].first > (transfer + 1)) {
                    // 더 빠른 길로, 더 빠르게 올 수 있었으면
                    transfer_count[next].first = (transfer + 1) % MOD;
                    transfer_count[next].second = 1;
                    dist[next] = next_cost;
                    pq.push({{next_cost, transfer + 1}, next});
                } else if (dist[next] == next_cost && transfer_count[next].first == (transfer + 1)) {
                    // 기존과 똑같은 최단최단경로 존재
                    transfer_count[next].second = (transfer_count[next].second + 1) % MOD;
                    pq.push({{next_cost, transfer + 1}, next});
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M >> X >> Y;
    map.resize(N + 1);

    for (int i = 0; i < M; i++) {
        cin >> u >> v >> w;
        map[u].emplace_back(v, w);
    }
    init();
    dijkstra();

    if (dist[Y] == INT64_MAX) cout << "-1\n";
    else {
        cout << dist[Y] << "\n";
        cout << transfer_count[Y].first << "\n";
        cout << transfer_count[Y].second % MOD << '\n';
    }

    return 0;
}