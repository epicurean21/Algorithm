/**
 * 1922 네트워크 연결
 * 최소 스패닝 트리
 */
#include <iostream>
#include <vector>
#include <queue>

using namespace std;
#define MAX 10001
int N, M, a, b, c, total_cost;
priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<>> edges;

int parent[MAX];

int find(int a) { // a의 부모가 무엇인지 찾자
    if (parent[a] == a) return a;
    return parent[a] = find(parent[a]);
}

void merge(int a, int b) {
    a = find(a);
    b = find(b);

    if (a == b) return;
    parent[a] = b;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> N >> M;
    for (int i = 1; i <= N; i++)
        parent[i] = i;

    while (M--) {
        cin >> a >> b >> c;
        edges.push({c, {a, b}}); // 간선 받음, pq를 이용해 오름차순 정렬 !
    }

    // 이제 간선을 하나 씩 연결해서, 사이클이 만들어지지 않는 spanning tree 중 minimum spanning tree를 만들어 보자 !
    while (!edges.empty()) {
        int from = edges.top().second.first;
        int to = edges.top().second.second;
        int cost = edges.top().first;
        edges.pop();

        // 간선을 추가 했을 때, 사이클이 만들어 지는지 확인하자
        // 어떻게 ? Union-find
        // 사전 필요한 것, 각 노드가 자기 자신을 부모로 갖고있는 초기화 배열
        if (find(from) == find(to)) continue;
        merge(from, to);
        total_cost += cost;
    }

    cout << total_cost << '\n';

    return 0;
}