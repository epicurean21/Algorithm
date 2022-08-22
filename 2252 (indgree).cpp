/**
 * 2252 줄 세우기
 * 위상 정렬
 * in-degree 가 0인 경우부터 탐색하는 방식
 */
#include <iostream>
#include <vector>
#include <queue>

using namespace std;
#define MAX 32001
int N, M, A, B;
vector<vector<int>> map;
vector<int> ans;
int indeg[MAX];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> N >> M;
    map.resize(N + 1);
    while (M--) {
        cin >> A >> B;
        map[A].emplace_back(B);
        indeg[B]++;
    }

    queue<int> topological_sort;

    for (int i = 1; i <= N; i++)
        if (!indeg[i])
            topological_sort.push(i);

    while (!topological_sort.empty()) {
        int cur = topological_sort.front();
        ans.emplace_back(cur);
        topological_sort.pop();
        for (int next: map[cur]) {
            indeg[next]--;
            if (!indeg[next])
                topological_sort.push(next);
        }
    }

    for (int i: ans) {
        cout << i << " ";
    }

    return 0;
}