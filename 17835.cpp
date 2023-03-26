/**
 * 17835 면접보는 승범이네
 * 다익스트라
 *
 * 풀이
 * ---
 * 모든 장소에서 면접보는 곳 까지의 거리의 최댓값을 구하면 넘 오래걸린다 (시간 초과)
 * map을 그릴 때, 역 방향으로 그린 뒤
 * 면접장소들로부터 다른 위치까지의 모든 거리를 구하고
 * 최댓값을 찾는다.
 */
#include "iostream"
#include "vector"
#include "unordered_set"
#include "queue"
#include "algorithm"

using namespace std;
#define MAX 100001
#define ll long long
int n, m, k, u, v, c;
ll distances[MAX];
vector<vector<pair<int, int>>> map(MAX);
pair<int, ll> answer;
unordered_set<int> interviewPlaces;

void init() {
    for (int i = 1; i <= n; i++) distances[i] = INT64_MAX;
}

void dijkstra(int start) {
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
    distances[start] = 0;
    pq.emplace(0, start);
    while (!pq.empty()) {
        int cur = pq.top().second;
        ll cur_cost = pq.top().first;
        pq.pop();

        if (distances[cur] < cur_cost) continue;
        for (auto &i: map[cur]) {
            int next = i.first;
            ll next_cost = i.second + cur_cost;

            if (next_cost <= distances[next]) {
                if (interviewPlaces.count(next) == 0) {
                    distances[next] = next_cost;
                    pq.emplace(next_cost, next);
                }
            }
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m >> k;
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> c;
        map[v].emplace_back(u, c);
    }
    for (int i = 0; i < k; i++) {
        cin >> u;
        interviewPlaces.emplace(u);
    }

    init();
    for (auto i: interviewPlaces) {
        dijkstra(i);
    }

    for (int i = 1; i <= n; i++) {
        if (!interviewPlaces.count(i)) {
            if (answer.second < distances[i]) {
                answer.first = i;
                answer.second = distances[i];
            }
        }
    }

    cout << answer.first << '\n' << answer.second << '\n';

    return 0;
}