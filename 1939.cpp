#include <iostream>
#include <vector>
#include <cstring>

using namespace std;
#define MAX 100001
#define INF 1000000000
int N, M, a, b, w, start_point, end_point, ans;
bool visited[MAX];
vector<vector<pair<int, int>>> map(MAX);

bool dfs(int cur, int w) {
    visited[cur] = true;
    if(cur == end_point)
        return true;
    for (auto n : map[cur]) {
        int next = n.first;
        int weight = n.second;
        if (!visited[next] && w <= weight) {
            if(!dfs(next, weight)) continue;
            else
                return true;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    for (int i = 0; i < M; i++) {
        cin >> a >> b >> w;
        map[a].push_back({b, w});
        map[b].push_back({a, w});
    }
    cin >> start_point >> end_point;
    int left = 0;
    int right = INF;
    while (left <= right) {
        int m = (left + right) / 2;
        if (dfs(start_point, m)) {
            ans = m;
            left = m + 1;
        } else
            right = m - 1;
        memset(visited, false, sizeof(visited));
    }
    cout << ans << "\n";
    return 0;
}