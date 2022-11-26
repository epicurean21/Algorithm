/**
 * 5719 거의 최단 경로
 * 그래프 탐색, 그래프 이론, 다익스트라, 너비우선탐색
 *
 * 거의최단경로란? -> 최단 경로에 포함되지 않는 엣지들만 이용한 경로 중 최단경로
 * 즉, 최단 경로가 두 개가 있다면 해당되는 엣지들은 모두 사용 불가.
 *
 * How to solve?
 * 1. Dijksta 1회 돌려서 최단 경로들을 찾는다.
 * - 찾으면서 최단 경로의 반대 방향 edge를 생성한다.
 * 2. 도착지로부터 BFS를 돌린다
 * - 돌리면서 edge를 -1로 만든다 (즉, 최단경로는 사용하지 못하도록)
 * 3. Dijkstra를 다시 돌린다.
 */
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;
#define MAX 502
int N, M, S, D, U, V, P;
bool chk[MAX][MAX];
vector<vector<pair<int, int>>> roads;
vector<vector<pair<int, int>>> reversed_roads;
vector<int> dist, ans;

void dijkstra_first(int s) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({0, s});
    dist[s] = 0;

    while (!pq.empty()) {
        int cur = pq.top().second;
        int cur_cost = pq.top().first;
        pq.pop();

        if (dist[cur] < cur_cost) continue;

        for (auto n: roads[cur]) {
            int next = n.first;
            int next_cost = n.second + cur_cost;

            if (dist[next] > next_cost) {
                dist[next] = next_cost;
                pq.push({next_cost, next});
                reversed_roads[next].clear();
                reversed_roads[next].emplace_back(cur, n.second);
            } else if (dist[next] == next_cost) {
                reversed_roads[next].emplace_back(cur, n.second);
            }
        }
    }
}

void bfs(int d) {
    queue<int> q;
    q.push(d);

    while (!q.empty()) {
        int cur = q.front();
        q.pop();

        for (auto n: reversed_roads[cur]) {
            int next = n.first;
            if (chk[cur][next]) continue;
            chk[cur][next] = true;

            for (int i = 0; i < roads[next].size(); i++)
                if (roads[next][i].first == cur)
                    roads[next][i].second = -1;
            q.push(next);
        }
    }
}

void dijkstra_second(int s) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({0, s});
    dist[s] = 0;

    while (!pq.empty()) {
        int cur = pq.top().second;
        int cur_cost = pq.top().first;
        pq.pop();

        if (ans[cur] < cur_cost) continue;

        for (auto n: roads[cur]) {
            int next = n.first;
            int next_cost = n.second;
            if (next_cost == -1) continue;

            if (ans[next] > next_cost + cur_cost) {
                ans[next] = next_cost + cur_cost;
                pq.push({next_cost + cur_cost, next});
            }
        }
    }
}

void init(int n) {
    roads.clear();
    reversed_roads.clear();
    dist.clear();
    ans.clear();
    roads.resize(n + 1);
    reversed_roads.resize(n + 1);
    dist.resize(n + 1, INT32_MAX);
    ans.resize(n + 1, INT32_MAX);
    memset(chk, false, sizeof(chk));
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    while (cin >> N >> M) {
        if (N == 0 && M == 0) break;

        init(N);

        cin >> S >> D;
        for (int i = 0; i < M; i++) {
            cin >> U >> V >> P;
            roads[U].emplace_back(V, P);
        }

        dijkstra_first(S);
        bfs(D);
        dijkstra_second(S);

        if (ans[D] == INT32_MAX) cout << "-1\n";
        else cout << ans[D] << "\n";
    }

    return 0;
}