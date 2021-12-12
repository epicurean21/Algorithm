/**
 * 5972 택배 배송 [골드 5]
 * 다익스트라, 그래프 이론
 */
#include <iostream>
#include <vector>
#include <queue>

using namespace std;
int N, M, C, A, B;
vector<vector<pair<int, int>>> map;
vector<int> dist;

void dijkstra() {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({0, 1});
    dist[1] = 0;
    while (!pq.empty()) {
        int cur = pq.top().second;
        int cost = pq.top().first;
        pq.pop();

        if (dist[cur] < cost) continue;
        for (auto &i : map[cur]) {
            int next = i.first;
            int next_cost = i.second + cost;

            if (dist[next] > next_cost) {
                dist[next] = next_cost;
                pq.push({next_cost, next});
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N >> M;
    dist.resize(N + 1, INT32_MAX);
    map.resize(N + 1);
    for (int i = 0; i < M; i++) {
        cin >> A >> B >> C;
        map[A].emplace_back(B, C);
        map[B].emplace_back(A, C);
    }
    dijkstra();
    dist[N] == INT32_MAX ? cout << "-1\n" : cout << dist[N] << '\n';

    return 0;
}