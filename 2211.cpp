#include <iostream>
#include <queue>
#include <vector>

using namespace std;
#define MAX 1001
#define INF 9999999
vector<vector<pair<int, int>>> map;
vector<int> ans;
vector<int> dist;

priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
int N, M, A, B, C;

void reset() {
    for (int i = 1; i <= N; i++)
        dist[i] = INF;
}

void dijkstra(int start, int val) {
    pq.push({val, start});
    dist[start] = 0;

    while (!pq.empty()) {
        int cd = pq.top().first;
        int cur = pq.top().second;
        pq.pop();

        if (dist[cur] < cd) continue;

        for (int i = 0; i < map[cur].size(); i++) {
            int nd = map[cur][i].second;
            int nxt = map[cur][i].first;

            if (dist[nxt] > nd + dist[cur]) {
                dist[nxt] = nd + dist[cur];
                pq.push({dist[nxt], nxt});
                ans[nxt] = cur;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> M;
    map.resize(N + 1);
    ans.resize(N + 1);
    dist.resize(N + 1);
    reset();

    for (int i = 0; i < M; i++) {
        cin >> A >> B >> C;
        map[A].push_back({B, C});
        map[B].push_back({A, C});
    }
    dijkstra(1, 0);

    cout << N - 1 << "\n";
    for (int i = 2; i <= N; i++)
        cout << ans[i] << " " << i << "\n";
    return 0;
}