#include <iostream>
#include <vector>
#include <queue>

using namespace std;
#define MAX 100010
#define ll long long
#define INF 98761423541
int N, M, visible[MAX];
vector<vector<pair<int, int>>> map(MAX);
ll dist[MAX];

void inf() {
    for (int i = 0; i < N; i++)
        dist[i] = INF;
}

void dijkstra(int start) { // 다익스트라
    dist[start] = 0;
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
    pq.push({0, start});
    while (!pq.empty()) {
        int cur = pq.top().second;
        ll cost = pq.top().first;
        pq.pop();
        if (dist[cur] < cost) continue;

        for (int i = 0; i < map[cur].size(); i++) {
            int next = map[cur][i].first;
            ll nextCost = map[cur][i].second + cost;
            if (dist[next] > nextCost) {
                dist[next] = nextCost;
                pq.push({nextCost, next});
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    for (int i = 0; i < N; i++)
        cin >> visible[i];
    visible[N - 1] = 0; // N - 1은 갈 수 있으므로 0으로
    for (int i = 0; i < M; i++) {
        int a, b, t;
        cin >> a >> b >> t;
        if (visible[a] || visible[b]) continue; // 못가는곳은 그냥 간선 갖다 버리자
        map[a].push_back({b, t});
        map[b].push_back({a, t});
    }
    inf();
    dijkstra(0);
    if (dist[N - 1] == INF)
        cout << "-1\n";
    else
        cout << dist[N - 1] << '\n';
    return 0;
}