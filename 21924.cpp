/**
 * 21924 도시 건설
 * 그래프 이론, 최소 신장 트리
 *
 * Kruskal Algorithm으로 최소 신장 트리를 구한다.
 * 그 다음, find() 메소드를 활용해서 O(N) 순회하여 그룹이 다른게 있는지 찾아낸다.
 */
#include <iostream>
#include <queue>

using namespace std;
#define MAX 100001
#define ll long long
int N, M, A, B, C, cnt;
ll total_cost;
priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<>> roads;
int par[MAX];

void init() {
    for (int i = 1; i <= N; i++)
        par[i] = i;
}

int find(int a) {
    if (par[a] == a)
        return par[a];

    return par[a] = find(par[a]);
}

bool merge(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) return false;

    a < b ? par[b] = a : par[a] = b;
    return true;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> N >> M;

    init();
    for (int i = 0; i < M; i++) {
        cin >> A >> B >> C;
        roads.push({C, {A, B}});
        total_cost += C;
    }

    while (!roads.empty()) {
        if (cnt == N - 1)
            break;
        int from = roads.top().second.first;
        int to = roads.top().second.second;
        int cost = roads.top().first;
        roads.pop();
        if (merge(from, to)) {
            total_cost -= cost;
            cnt++;
        }
    }

    for (int i = 2; i <= N; i++) {
        if (find(1) != find(i)) {
            cout << "-1\n";
            return 0;
        }
    }

    cout << total_cost << "\n";
    return 0;
}