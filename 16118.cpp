/**
 * 16118 달빛 여우
 * 다익스트라, 그래프 이론
 */
#include "iostream"
#include "vector"
#include "queue"

using namespace std;
#define MAX 4002
#define ll long long
int n, m, a, b, d, ans;
pair<ll, ll> distsForWolf[MAX]; // 이전에 뛰어 온거, 뛰지 않고 온거
ll distsForFox[MAX];
vector<vector<pair<int, int>>> map(MAX);

void dijkstraForWolf(int start) {
    priority_queue<pair<ll, pair<int, bool>>, vector<pair<ll, pair<int, bool>>>, greater<>> pq;
    distsForWolf[start].second = 0;
    pq.push({0, {start, false}});
    while (!pq.empty()) {
        int cur = pq.top().second.first;
        bool isRunning = pq.top().second.second;
        ll curCost = pq.top().first;
        pq.pop();

        if (isRunning && distsForWolf[cur].first < curCost) continue;
        else if (!isRunning && distsForWolf[cur].second < curCost) continue;

        for (int i = 0; i < map[cur].size(); i++) {
            int next = map[cur][i].first;
            ll nextCost;
            if (!isRunning) { // 이전에 뛰지 않고 왔는지
                nextCost = curCost + (map[cur][i].second / 2);
                if (nextCost <= distsForWolf[next].first) { // 뛰어서 갔을 때 보다 작거나 같은지.
                    distsForWolf[next].first = nextCost;
                    pq.push({nextCost, {next, true}});
                }
            } else { // 이전에 뛰어 왔는지
                nextCost = curCost + (map[cur][i].second * 2);
                if (nextCost <= distsForWolf[next].second) {
                    distsForWolf[next].second = nextCost;
                    pq.push({nextCost, {next, false}});
                }
            }
        }
    }
}

void dijkstraForFox(int start) {
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
    distsForFox[start] = 0;
    pq.emplace(0, start);
    while (!pq.empty()) {
        int cur = pq.top().second;
        ll curCost = pq.top().first;
        pq.pop();

        if (distsForFox[cur] < curCost) continue;
        for (int i = 0; i < map[cur].size(); i++) {
            int next = map[cur][i].first;
            ll nextCost = map[cur][i].second + curCost;
            if (distsForFox[next] > nextCost) {
                distsForFox[next] = nextCost;
                pq.emplace(nextCost, next);
            }
        }
    }
}

void init() {
    for (int i = 1; i <= n; i++) {
        distsForWolf[i].first = distsForWolf[i].second = INT64_MAX;
        distsForFox[i] = INT64_MAX;
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> a >> b >> d;
        map[a].emplace_back(b, d * 2);
        map[b].emplace_back(a, d * 2);
    }

    init();
    dijkstraForWolf(1);
    dijkstraForFox(1);

    for (int i = 2; i <= n; i++)
        if (distsForFox[i] < distsForWolf[i].first && distsForFox[i] < distsForWolf[i].second)
            ans++;

    cout << ans << '\n';
    return 0;
}