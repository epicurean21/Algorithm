/**
 * 5719 거의 최단 경로
 * 다익스트라, 그래프 이론
 * - 거의 최단 경로란, 최단 경로에 포함되는 간선을 제외한 최단 경로를 찾자
 * - 함정 1: 최단 경로 값이 여러개라면, 해당 간선들은 사용해선 안된다.
 *
 * 풀이 방법:
 * 1. Dijkstra를 돌려서 시작점 부터 각 점까지 최단 경로를 찾고 저장한다.
 * 2. BFS 를 역그래프 (도착지 -> 출발지)로 순회하여 최단 경로를 삭제한다.
 *      ** 이게 핵심, 역방향으로 돌려야, 올바르게 최단 경로를 삭제한다.
 * 3. 순방향그래프로 다시 Dijkstra를 돌려 최단 경로를 찾는다.
 */

#include <iostream>
#include <vector>
#include <queue>

using namespace std;
#define MAX 501
int N, M, S, D, U, V, P, dist[MAX];
bool chk[MAX];
vector<vector<pair<int, int>>> map;
vector<vector<int>> reversed_map;
priority_queue<pair<int, int>> pq;

void init() {
    map.clear();
    reversed_map.clear();
    map.resize(N + 1);
    reversed_map.resize(N + 1);
    while (!pq.empty()) pq.pop();
    for (int i = 0; i < N; i++) {
        dist[i] = INT32_MAX;
        chk[i] = false;
    }
}

void find_dijkstra() {
    pq.push({0, S});
    dist[S] = 0;

    while (!pq.empty()) {
        int cur = pq.top().second;
        int cost = pq.top().first;
        pq.pop();

        if (dist[cur] < cost) continue;

        for (auto &i: map[cur]) {
            int next = i.first;
            int next_cost = i.second;
            if (next_cost == -1) continue; // 삭제 된 간선

            if (dist[next] > next_cost + cost) {
                dist[next] = next_cost + cost;
                reversed_map[next].clear();
                reversed_map[next].emplace_back(cur);
                pq.push({next_cost, next});
            } else if (dist[next] == next_cost + cost) {
                reversed_map[next].emplace_back(cur);
            }
        }
    }
}

void bfs_remove_edges() {
    queue<int> q;
    q.push(D);

    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        if (chk[cur]) continue;
        chk[cur] = true;
        for (auto &i: reversed_map[cur]) {
            int next = i;
            for (auto &j: map[i]) {
                if (j.first == cur) j.second = -1;
            }
            q.push(next);
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    while (true) {
        cin >> N >> M;
        if (N == 0 && M == 0) break;
        init();
        cin >> S >> D;
        for (int i = 0; i < M; i++) {
            cin >> U >> V >> P;
            map[U].emplace_back(V, P);
        }

        find_dijkstra();
        bfs_remove_edges();
        for (int i = 0; i < N; i++) dist[i] = INT32_MAX;
        find_dijkstra();

        if (dist[D] == INT32_MAX) cout << "-1\n";
        else cout << dist[D] << '\n';
    }
    return 0;
}