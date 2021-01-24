#include <iostream>
#include <queue>
#include <vector>

using namespace std;
#define INF 987654321
#define MAX 20001
int V, E, startV, a, b, w;
int dist[MAX];
vector<vector<pair<int, int>>> graph;
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
// priority_queue 의 가중치, a , b

void init() {
    for (int i = 1; i <= V; i++)
        dist[i] = INF;
}

void dijkstra(int start) {
    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int cur = pq.top().second;
        int weight = pq.top().first;
        pq.pop();

        // cur 주변을 탐색
        for (int i = 0; i < graph[cur].size(); i++) {
            int next = graph[cur][i].first;
            int next_weight = graph[cur][i].second + weight; // 현재 -> 다음으로 이동할 때 드는 비용

            if (next_weight < dist[next]) {
                dist[next] = next_weight;
                pq.push({next_weight, next});
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> V >> E >> startV;
    graph.resize(V + 1);
    for (int i = 0; i < E; i++) {
        cin >> a >> b >> w;
        graph[a].push_back({b, w}); // a -> b 로 가중치 w
    }

    init(); // 모든 가중치를 무한대로 초기화
    dijkstra(startV);
    // 출력
    for (int i = 1; i <= V; i++) {
        if (dist[i] == INF)
            cout << "INF\n";
        else
            cout << dist[i] << "\n";
    }
    return 0;
}