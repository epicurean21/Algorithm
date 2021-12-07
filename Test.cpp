#include <iostream>
#include <queue>
#include <vector>
#include <map>

using namespace std;
#define ll long long
int N, M, u, v, w, X, Z, P;
map<int, int> p;
vector<ll> dist, dist2;
vector<vector<pair<int, int>>> road;

void init() {
    for (int i = 1; i <= N; i++) {
        dist[i] = INT64_MAX;
        dist2[i] = INT64_MAX;
    }
}

void dijkstra(int start) {
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq_for_second;
    pq.push({0, start});
    dist[start] = 0;

    while (!pq.empty()) {
        int cur = pq.top().second;
        ll weight = pq.top().first;
        pq.pop();

        if (dist[cur] < weight) continue;

        for (auto &i : road[cur]) {
            int next = i.first;
            ll next_weight = i.second + weight;

            if (dist[next] > next_weight) {
                dist[next] = next_weight;
                pq.push({next_weight, next});
                if (p.count(next)) {
                    pq_for_second.push({dist[next], next});
                }
            }
        }
    }

    if (pq_for_second.empty()) return;

    dist2[pq_for_second.top().second] = pq_for_second.top().first;

    while (!pq_for_second.empty()) {
        int cur = pq_for_second.top().second;
        ll weight = pq_for_second.top().first;
        pq_for_second.pop();

        if (dist2[cur] < weight) continue;

        for (auto &i : road[cur]) {
            int next = i.first;
            ll next_weight = i.second + weight;

            if (dist2[next] > next_weight) {
                dist2[next] = next_weight;
                pq_for_second.push({next_weight, next});
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    road.resize(N + 1);
    dist.resize(N + 1);
    dist2.resize(N + 1);

    for (int i = 0; i < M; i++) {
        cin >> u >> v >> w;
        road[u].emplace_back(v, w);
        road[v].emplace_back(u, w);
    }

    cin >> X >> Z >> P;

    for (int i = 0; i < P; i++) {
        cin >> v;
        p.insert({v, i});
    }

    init();
    dijkstra(X);
    if (dist2[Z] == INT64_MAX) cout << "-1\n";
    else cout << dist2[Z] << '\n';

    return 0;
}