/**
 * 13023 ABCDE
 * 그래프 이론, 너비 우선 탐색
 */
#include <iostream>
#include <vector>
#include <cstring>

using namespace std;
#define MAX 2001
int N, M, a, b, ans;
bool visited[MAX];
vector<vector<int>> map;

void dfs(int cur, int cnt) {
    visited[cur] = true;
    if (cnt == 5) {
        ans = 1;
        return;
    }
    for (int i: map[cur])
        if (!visited[i])
            dfs(i, cnt + 1);
    visited[cur] = false; // for 문 돌고나서 방문 해제 해줘야 끝부분 조건을 맞춰줄 수 있다.
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    map.resize(N + 1);
    for (int i = 0; i < M; i++) {
        cin >> a >> b;
        map[a].emplace_back(b);
        map[b].emplace_back(a);
    }

    for (int i = 0; i < N; i++) {
        memset(visited, false, sizeof(visited));
        dfs(i, 1);
        if (ans) break;
    }
    cout << ans << '\n';
    return 0;
}