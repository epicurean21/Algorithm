#include <iostream>
#include <queue>
#include <vector>

using namespace std;
#define ll long long
#define MAX 5010
#define INF 10987654321
int N, M, A, B, L, t1, t2;
vector<vector<pair<pair<int, ll>, bool>>> map(MAX);
ll dist[MAX], ans, S, E;

void init() {
    for (int i = 0; i <= N; i++)
        dist[i] = INF;
}

void dijkstra(int start) {
    dist[start] = 0;
    priority_queue<pair<ll, int>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        int cur = pq.top().second;
        ll cost = pq.top().first;
        pq.pop();
        if (dist[cur] < cost) continue;

        for (int i = 0; i < map[cur].size(); i++) {
            int next = map[cur][i].first.first;
            ll timeCost = map[cur][i].first.second;
            bool isTraffic = map[cur][i].second; // true = 퇴근시간 정체, false, 정체 x

            // 퇴근시간에 겹칠때 다르게 계산하자
            if (isTraffic) {
                ll nextCost;
                if (dist[cur] < S) { // 퇴근시간 아님
                    if (dist[cur] + timeCost >= S) { // 막힐시간에 들어감
                        ll speed = S - dist[cur];
                        ll last = timeCost - speed;
                        ll start = min((ll) E - S, last * 2);
                        ll fin = last - start / 2;
                        nextCost = dist[cur] + speed + start + fin;
                    } else
                        nextCost = dist[cur] + timeCost;
                } else {
                    if (dist[cur] < E) {
                        ll start = min(E - dist[cur], timeCost * 2);
                        ll last = timeCost - start / 2;
                        nextCost = dist[cur] + start + last;
                    } else
                        nextCost = dist[cur] + timeCost;
                }

                if (dist[next] > nextCost) {
                    dist[next] = nextCost;
                    pq.push({nextCost, next});
                }
            } else { // 정체없음 걍 가면댐
                if (dist[next] > timeCost + dist[cur]) {
                    dist[next] = dist[cur] + timeCost;
                    pq.push({dist[cur] + timeCost, next});
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M >> S >> E;
    S *= 2;
    E *= 2;
    for (int i = 0; i < M; i++) {
        cin >> A >> B >> L >> t1 >> t2;
        map[A].push_back({{B, L * 2}, t1}); // A -> B로 거리 L, t1이 1이면 정체, 0이면 아님
        map[B].push_back({{A, L * 2}, t2});
    }

    init();
    dijkstra(1);
    for (int i = 1; i <= N; i++)
        ans = max(ans, dist[i]);
    if (ans & 1) printf("%lld.5\n", ans / 2);
    else printf("%lld\n", ans / 2);
    return 0;
}