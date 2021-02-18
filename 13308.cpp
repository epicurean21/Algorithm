#include <iostream>
#include <vector>
#include <queue>

using namespace std;
#define MAX 2501
#define ll long long
int N, M, A, B, C;
ll fuel[MAX], ans = -1;
vector<vector<pair<int, int>>> map(MAX);
priority_queue<pair<ll, pair<int, int>>, vector<pair<ll, pair<int, int>>>, greater<pair<ll, pair<int, int>>>> pq;
int chk[MAX][MAX];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    for (int i = 1; i <= N; i++)
        cin >> fuel[i];
    for (int i = 0; i < M; i++) {
        cin >> A >> B >> C;
        map[A].push_back({B, C});
        map[B].push_back({A, C});
    }

    pq.push({0, {1, fuel[1]}});
    while (!pq.empty()) {
        int cur = pq.top().second.first;
        ll cost = pq.top().first;
        ll curCost = pq.top().second.second;

        pq.pop();

        if (chk[cur][curCost] == true) continue;
        chk[cur][curCost] = true;

        if (cur == N) {
            ans = cost;
            break;
        }

        for (int i = 0; i < map[cur].size(); i++) {
            int next = map[cur][i].first;
            int nextCost = map[cur][i].second;
            ll minimumCost = min(fuel[next], curCost);
            ll totalCost = cost + nextCost * curCost;
            pq.push({totalCost, {next, minimumCost}});
        }
    }
    cout << ans << '\n';
    return 0;
}