/**
 * 20168 골목 대장 효석 - 기능성
 * 다익스트라, 그래프 이론
 */
#include <iostream>
#include <vector>
#include <queue>

using namespace std;
#define MAX 100001
#define ll long long
int N, M, A, B, C, a, b, c, cost[MAX]; // max_cost
vector<vector<pair<int, int>>> map;
priority_queue<pair<pair<ll, int>, int>> pq; // total_cost & max_cost & next

int max(int x, int y) {
    return x > y ? x : y;
}

void dijkstra() {
    pq.push({{0, 0}, A});
    cost[A] = 0;

    while (!pq.empty()) {
        int cur = pq.top().second;
        ll total_cost = pq.top().first.first;
        int max_cost = pq.top().first.second;


        pq.pop();

        if (cost[cur] < max_cost) return;

        cost[cur] = max_cost;

        for (auto i: map[cur]) {
            int next = i.first;
            int next_cost = i.second;
            ll next_total_cost = next_cost + total_cost;

            if (next_total_cost <= C) {
                pq.push({{next_total_cost, max(next_cost, max_cost)}, next});
            }
        }
    }

}

void init() {
    map.resize(N + 1);
    for (int i = 1; i <= N; i++)
        cost[i] = INT32_MAX;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> N >> M >> A >> B >> C;
    init();

    for (int i = 0; i < M; i++) {
        cin >> a >> b >> c;
        map[a].emplace_back(b, c);
        map[b].emplace_back(a, c);
    }

    dijkstra();

    if (cost[B] == INT32_MAX) cout << "-1\n";
    else cout << cost[B] << "\n";


    return 0;
}