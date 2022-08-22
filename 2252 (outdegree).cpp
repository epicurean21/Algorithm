/**
 * 2252 줄 세우기
 * 위상 정렬
 * out-degree 가 0인 경우부터 탐색하는 방식
 * DFS
 */
#include <iostream>
#include <stack>
#include <vector>

using namespace std;
#define MAX 32001
int N, M, A, B;
bool visited[MAX];
vector<vector<int>> map;
stack<int> ans;

void dfs(int cur) {
    if (visited[cur])
        return;

    visited[cur] = true;
    for (int i: map[cur])
        if (!visited[i])
            dfs(i);

    ans.push(cur);
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> N >> M;
    map.resize(N + 1);
    while (M--) {
        cin >> A >> B;
        map[A].emplace_back(B);
    }

    for (int i = 1; i <= N; i++)
        if (!visited[i])
            dfs(i);

    while (!ans.empty()) {
        cout << ans.top() << " ";
        ans.pop();
    }

    return 0;
}