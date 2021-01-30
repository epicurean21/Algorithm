#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;
#define MAX 10001
int N, a, b, w, outDeg[MAX], ans, startP;
vector<vector<pair<int, int>>> tree;
queue<pair<int, int>> q;
bool chk[MAX];

int max(int a, int b) {
    return a > b ? a : b;
}

void dfs(int cur, int w) {
    chk[cur] = true;
    if (w > ans) {
        startP = cur;
        ans = w;
    }

    for (int i = 0; i < tree[cur].size(); i++) {
        int next = tree[cur][i].first;
        int weight = tree[cur][i].second;
        if (!chk[next])
            dfs(next, w + weight);
    }
}

void bfs(int cur) {
    q.push({cur, 0});
    while (!q.empty()) {
        int now = q.front().first;
        int w = q.front().second;
        q.pop();
        chk[now] = true;
        for (int i = 0; i < tree[now].size(); i++) {
            int next = tree[now][i].first;
            int weight = tree[now][i].second;
            if (!chk[next]) {
                ans = max(ans, w + weight);
                q.push({next, w + weight});
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    tree.resize(N + 1);
    for (int i = 0; i < N - 1; i++) { // input
        cin >> a >> b >> w;
        tree[a].push_back({b, w});
        tree[b].push_back({a, w});
    }
    if (N == 2) {
        cout << tree[1][0].second << '\n';
        return 0;
    }
    dfs(1, 0);
   // cout << startP << '\n';
    memset(chk, false, sizeof(chk));
    bfs(startP);
    cout << ans << '\n';
    return 0;
}
/*

5
1 2 3
1 3 4
2 4 9
2 5 9
    18

12
1 2 3
1 3 2
2 4 5
3 5 11
3 6 9
4 7 1
4 8 7
5 9 15
5 10 4
6 11 6
6 12 10
    45

5
1 2 33
2 3 34
1 4 22
1 5 10
    89
*/
/*

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;
#define MAX 10001
int N, a, b, w, outDeg[MAX], ans;
vector<vector<pair<int, int>>> tree;
queue<int> q;
bool chk[MAX];

int max(int a, int b) {
    return a > b ? a : b;
}

void dfs(int cur, int w) {
    chk[cur] = true;
    if (outDeg[cur] == 0) { // 다른 Leaf에 도달했다면 지름 길이 max로 최신화
        ans = max(ans, w);
    }

    for (int i = 0; i < tree[cur].size(); i++) {
        int next = tree[cur][i].first;
        int weight = tree[cur][i].second;
        if (!chk[next]) {
            dfs(next, w + weight);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    tree.resize(N + 1);
    for (int i = 0; i < N - 1; i++) { // input
        cin >> a >> b >> w;
        tree[a].push_back({b, w});
        tree[b].push_back({a, w});
        outDeg[a]++;
    }
    if (N == 2) {
        cout << tree[1][0].second << '\n';
        return 0;
    }
    for (int i = 1; i <= N; i++)  // find leaf node
        if (outDeg[i] == 0)
            q.push(i);

    while (!q.empty()) { // DFS순회, 모든 Leaf
        memset(chk, false, sizeof(chk)); // 방문 정점 초기화
        dfs(q.front(), 0);
        q.pop();
    }
    cout << ans << '\n';
    return 0;
}
*/
