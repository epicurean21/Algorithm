#include <iostream>
#include <queue>
#include <vector>
#include <map>

using namespace std;
#define ll long long
int N, M, u, v, w, X, Z, P;
map<int, int> p;
vector<ll> dist;
vector<vector<pair<int, int>>> road;

void init() {
    for (int i = 1; i <= N; i++)
        dist[i] = INT64_MAX;
}

void dijkstra(int start, int end) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq_for_second;
    pq.push({start, 0});
    dist[start] = 0;

    while (!pq.empty()) {
        int cur = pq.top().first;
        int weight = pq.top().second;

        if (dist[cur] < weight) continue;

        for (auto &i : road[cur]) {
            int next = i.first;
            int next_weight = i.second;

            if (dist[next] > weight + next_weight) {
                dist[next] = weight + next_weight;
                pq.push({next, weight + next_weight});
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
    for (int i = 0; i < M; i++) {
        cin >> u >> v >> w;
        road[u].emplace_back(v, w);
        road[v].emplace_back(u, w);
    }

    cin >> X >> Z >> P;

    for (int i = 0; i < P; i++) {
        cin >> v;
        p.insert({i, v});
    }

    init();


    return 0;
}