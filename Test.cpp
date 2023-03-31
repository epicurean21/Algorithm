/**
 * 13911 집 구하기
 * 다익스트라, 그래프 이론
 */
#include "iostream"
#include "vector"

using namespace std;
int V, E, u, v, w, M, S, x, y;
vector<pair<int, int>> dists;
vector<vector<pair<int, int>>> map;
vector<int> mcdonalds, starbucks;

void dijkstra() {

}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> V >> E;
    map.resize(V + 1);
    dists.resize(V + 1);
    for (int i = 0; i < E; i++) {
        cin >> u >> v >> w;
        map[u].emplace_back(v, w);
        map[v].emplace_back(u, w);
    }
    cin >> M >> x;
    for (int i = 0; i < M; i++) {
        cin >> u;
        mcdonalds.emplace_back(u);
    }
    cin >> S >> y;
    for (int i = 0; i < S; i++) {
        cin >> u;
        starbucks.emplace_back(u);
    }

    return 0;
}