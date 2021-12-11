#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;
#define INF (long long)1e18
#define ll long long

int N, M;
ll S, E;

struct Home {
    int v;
    ll len;
    bool stock;

    Home() {}

    Home(int vv, ll longlong, bool ss) : v(vv), len(longlong), stock(ss) {}
};

vector<Home> adj[5001];

ll dijkstra(int start) {
    vector<ll> dist(N + 1, INF);
    priority_queue<pair<ll, int>> pq;
    dist[start] = 0;

    pq.push({0, start});

    while (!pq.empty()) {
        int here = pq.top().second;
        ll cost = -pq.top().first;

        pq.pop();

        if (dist[here] < cost) continue;
        for (auto const &n : adj[here]) {
            int next = n.v;
            ll len = n.len;
            if (n.stock) {
                ll ncost;
                if (dist[here] < S) {
                    if (dist[here] + len >= S) {
                        ll diff = S - dist[here];        //S시간보다 작을 때 일반속도로 감
                        ll last = len - diff;
                        ll st = min(E - S, last * 2);        //S시간이상 E시간 미만일때 정체속도
                        ll fin = last - st / 2;                    //E시간보다 커졌을 때 일반속도
                        ncost = dist[here] + diff + st + fin;
                    } else
                        ncost = dist[here] + len;
                } else {
                    if (dist[here] >= E) {
                        ncost = dist[here] + len;
                    } else {
                        ll st = min(E - dist[here], len * 2);
                        ll last = len - st / 2;
                        ncost = dist[here] + st + last;
                    }
                }
                if (dist[next] > ncost) {
                    dist[next] = ncost;
                    pq.push({-ncost, next});
                }
            } else {
                ll ncost = dist[here] + len;
                if (dist[next] > ncost) {
                    dist[next] = ncost;
                    pq.push({-ncost, next});
                }
            }
        }
    }

    ll ret = 0;

    for (int n = 1; n <= N; n++)
        ret = max(ret, dist[n]);

    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N >> M >> S >> E;

    S *= 2, E *= 2;

    for (int m = 0; m < M; m++) {
        int u, v, l, t1, t2;
        cin >> u >> v >> l >> t1 >> t2;
        adj[u].emplace_back(Home(v, (long long) l * 2, t1));
        adj[v].emplace_back(Home(u, (long long) l * 2, t2));
    }

    long long ans = dijkstra(1);

    if (ans & 1)
        printf("%lld.5\n", ans / 2);
    else cout << ans / 2 << '\n';

    return 0;
}