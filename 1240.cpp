#include <iostream>
#include <vector>
#include <queue>

using namespace std;
#define MAX 1002

int min(int x, int y) {
    return x > y ? y : x;
}

int N, M, a, b, d;
vector<vector<pair<int, int>>> tree(MAX);
bool been[MAX];
queue<pair<int, int>> q;

void reset() {
    for (int i = 0; i < MAX; i++)
        been[i] = false;
    while(!q.empty())
        q.pop();
}

int bfs(int a, int b) {
    q.push({a, 0});
    been[a] = true;
    while (!q.empty()) {
        int cur = q.front().first;
        int cnt = q.front().second;
        q.pop();
        if (cur == b)
            return cnt;

        for (int i = 0; i < tree[cur].size(); i++) {
            int next = tree[cur][i].first;
            if (!been[next]) {
                been[tree[cur][i].first] = true;
                int dis = tree[cur][i].second;
                q.push({tree[cur][i].first, cnt + dis});
            }
        }
    }
    return -1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> M;
    for (int i = 0; i < N - 1; i++) {
        cin >> a >> b >> d;
        tree[a].push_back({b, d});
        tree[b].push_back({a, d});
    }
    for (int i = 0; i < M; i++) {
        cin >> a >> b;
        cout << bfs(a, b) << "\n";
        reset();
    }
    return 0;
}