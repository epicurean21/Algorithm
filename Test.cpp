/**
 * 10217 KCM Travel
 * 다익스트라, 그래프 이론, 다이나믹 프로그레밍
 *
 * 인천: 1번, LA: N번
 * 1 -> N 까지 M 원 이하이면서 최단경로
 * 각 지역별로 얼마남았는지를 계산하면서 최단경로를 찾으면 될듯?
 */
#include "iostream"
#include "vector"
#include "queue"

using namespace std;
#define N_MAX 101
#define M_MAX 10001
int t, n, m, k, u, v, c, d;
string impossible = "Poor KCM\n";
vector<vector<pair<int, pair<int, int>>>> map; // {to, dist, cost}
priority_queue<pair<pair<int, int>, int>, vector<pair<pair<int, int>, int>>, greater<>> pq; // dist, cost, next
int dist[N_MAX][M_MAX];

void init() {
    map.clear();
    map.resize(n + 1);
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= m; j++)
            dist[i][j] = INT32_MAX;

    while (!pq.empty()) pq.pop();
}

void dijkstra() {
    pq.push({{0, 0}, 1});
    dist[1][0] = 0;
    while (!pq.empty()) {
        int cur = pq.top().second;
        int cur_dist = pq.top().first.first;
        int cur_cost = pq.top().first.second;
        pq.pop();

        if (dist[cur][cur_cost] < cur_dist) continue;

        for (auto &i: map[cur]) {
            int next = i.first;
            int next_dist = i.second.first + cur_dist;
            int next_cost = i.second.second + cur_cost;

            if (next_cost > m) continue;

            if (next_dist < dist[next][next_cost]) {
                for (int j = next_cost; j <= m; j++) {
                    if (dist[next][j] <= next_dist) break;
                    dist[next][j] = next_dist;
                }
                pq.push({{next_dist, next_cost}, next});
            }
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> t;
    cin >> n >> m >> k;

    init();
    while (k--) {
        cin >> u >> v >> c >> d;
        map[u].push_back({v, {d, c}});
    }

    dijkstra();

    int ans = INT32_MAX;
    for (int i = 0; i <= m; i++) if (dist[n][i] < INT32_MAX) ans = dist[n][i];

    if (ans == INT32_MAX) cout << impossible;
    else cout << ans << "\n";

    return 0;
}