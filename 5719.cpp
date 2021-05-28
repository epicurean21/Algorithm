#include <iostream>
#include <vector>
#include <queue>

using namespace std;
#define MAX 501
int N, M, S, D, U, V, P;

pair<int, int> map[MAX];
vector<int> predecessor;

int dijkstra(int s, int d) {
    vector<int> final_distance;
    vector<int> dist(N + 1, INT32_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    dist[s] = 0;
    pq.push({0, s});

    while (!pq.empty()) {
        int cur = pq.top().second;
        int cost = pq.top().first;
        pq.pop();

        if (dist[cur] < cost) continue;

        for (int i = 0; i < N; i++) {
            if (map[cur][i].second == -1) continue;
            int next = map[cur][i].first;
            int nextCost = map[cur][i].second + cost;

            if (dist[next] > nextCost) {
                dist[next] = nextCost;
                predecessor.clear();
            } else if (dist[next] >= nextCost) {
                predecessor
            }
        }
    }
    return dist[d];
}

void remove_edges(int S, int D, int cur) {
    if (now == S) return;

    if (visited[now]) return;
    visited[now] = true;

    for (int i = 0; i < pre[now].size(); i++) {
        int next = pre[now][i];
        adj[next][now] = -1;
        deletePath(pre[now][i]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    while (cin >> N >> M) {
        if (N == 0 && M == 0)
            break;
        map.clear();
        predecessor.clear();
        map.resize(N + 1);

        cin >> S >> D;
        for (int i = 0; i < M; i++) {
            cin >> U >> V >> P;
            map[U].emplace_back(V, P);
        }

        int dist = dijkstra(S, D);
        if (dist == -1) {
            cout << "-1\n";
            return 0;
        }
    }
    return 0;
}