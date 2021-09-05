/**
 * 20010: 악덕 영주 혜유
 * 최소 신장 트리로 풀자
 * 모든 마을을 연결하는 최소 비용은 그냥 단순 MST라고 할 수 있다.
 * 그럼 마을 <-> 마을중 최대 비용은 어떻게 구할까
 *
 * My Idea: Indeg 개수로 생각해보자
 * 결국 최대한 많은 집을 돌아야 가장 많은 cost를 사용할 것
 * 그러면 Indeg 가 1인 경우의 집끼리의 거리가 가장 멀 것이다. 또는 OutDeg == 1 인 경우?
 * MST 의 지름을 구하는거임
 * degree 가 1인 녀석들만 dfs를 돌려서 거리가 가장 먼걸 찾자
 */

#include <iostream>
#include <vector>
#include <queue>

using namespace std;
#define MAX 1002
int N, K, a, b, c, p[MAX], total_cost, max_cost, degree[MAX];
priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<>> pq;
vector<vector<pair<int, int>>> map;

int max(int x, int y) {
    return x > y ? x : y;
}

void init(int n) {
    for (int i = 0; i <= n; i++)
        p[i] = i;

    map.resize(n + 1);
}

int find(int x) {
    if (p[x] == x) return x;
    return p[x] = find(p[x]);
}

void merge(int x, int y) {
    x = find(x);
    y = find(y);

    p[x] = y;
}

int dfs(int cur, int pre) {
    int res = 0;
    for (auto &next : map[cur]) {
        if (next.first != pre) {
            res = max(res, dfs(next.first, cur) + next.second);
        }
    }

    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> K;

    init(N);
    for (int i = 0; i < K; i++) {
        cin >> a >> b >> c;
        pq.push({c, {a, b}});
    }

    while (!pq.empty()) {
        int x = pq.top().second.first;
        int y = pq.top().second.second;
        int cost = pq.top().first;

        pq.pop();

        if (find(x) == find(y)) continue;

        merge(x, y);
        degree[x]++;
        degree[y]++;
        map[x].emplace_back(y, cost);
        map[y].emplace_back(x, cost);

        total_cost += cost;
    }

    for (int i = 0; i < N; i++)
        if (degree[i] == 1)
            max_cost = max(max_cost, dfs(i, -1));

    cout << total_cost << "\n" << max_cost << "\n";

    return 0;
}