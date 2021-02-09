#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;
#define MAX 2000002
int N, M, K, A, B, C;
vector<vector<pair<int, int>>> graph;
priority_queue<int> dist[MAX];
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

void dijkstra(int start) {
    dist[start].push(0);
    pq.push({0, start});

    while (!pq.empty()) {
        int cur = pq.top().second;
        int cost = pq.top().first;
        pq.pop();

        for (int i = 0; i < graph[cur].size(); i++) {
            int next = graph[cur][i].first;
            int nextCost = graph[cur][i].second;

            if (dist[next].size() < K) { // k보다 적음
                dist[next].push(cost + nextCost);
                pq.push({cost + nextCost, next});
            } else if (dist[next].top() > nextCost + cost) { // k개보다 많음
                dist[next].pop();
                dist[next].push(cost + nextCost);
                pq.push({cost + nextCost, next});
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M >> K;
    graph.resize(N + 1);
    for (int i = 0; i < M; i++) {
        cin >> A >> B >> C;
        graph[A].push_back({B, C});
    }
    dijkstra(1);
    for (int i = 1; i <= N; i++) {
        if (dist[i].size() < K) cout << "-1\n";
        else cout << dist[i].top() << "\n";
    }
    return 0;
}