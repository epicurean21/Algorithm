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

#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
#include <cstdio>

#define MAX_V 20001

using namespace std;

// 그래프의 인접 리스트. (연결된 정점 번호, 간선 가중치) 쌍을 담아야 한다.
vector<pair<int, int>> adj[MAX_V]; // 정점의 최대 개수 :: MAX_V

vector<int> dijkstra(int src, int V, int E) {
    // V만큼 배열을 INT_MAX로 초기화
    vector<int> dist(V, INT_MAX);
    dist[src] = 0; // 시작점은 0으로 초기화 한다.

    priority_queue<pair<int, int> > pq;

    pq.push(make_pair(0, src)); // 시작점을 처음으로 우선순위 큐에 삽입

    while (!pq.empty()) {
        // 우선순위 큐에 음의 가중치로 들어가 있으니 양으로 바꾸어준다.
        int cost = -pq.top().first;
        int here = pq.top().second;

        pq.pop();

        // 만약 지금 꺼낸 것보다 더 짧은 경로를 알고 있다면 지금 꺼낸것을 무시한다.
        if (dist[here] < cost)
            continue;

        // 인접한 정점들을 모두 검사.
        for (int i = 0; i < adj[here].size(); i++) {
            int there = adj[here][i].first;
            int nextDist = cost + adj[here][i].second;

            // 더 짧은 경로를 발견하면, dist[]를 갱신하고 우선순위 큐에 넣는다.
            // dist 벡터에는 시작점 -> there 위치까지의 최단 거리가 담겨있다.
            if (dist[there] > nextDist) {
                dist[there] = nextDist;
                pq.push(make_pair(-nextDist, there));
                /*
                여기서 -로 넣는 이유?
                priority_queue STL은 기본적으로 가장 큰 원소가 위로 가도록 큐를 구성
                따라서 거리의 부호를 바꿔서 거리가 작은 정점부터 꺼내지도록 하기 위함
                */
            }
        }
    }

    return dist;
}