#include <iostream>
#include <vector>
#include <queue>

using namespace std;
#define MAX 101
#define INF -98765432
int n, m, u, v, w, dist[MAX];
vector<vector<pair<int, int>>> map(MAX);
vector<int> rev[MAX];
vector<int> ans;
bool chk[MAX], cycle;
int pre[MAX];
queue<int> q;

int max(int a, int b) {
    return a > b ? a : b;
}

void init() {
    for (int i = 0; i < MAX; i++)
        dist[i] = INF;
    dist[1] = 0;
}

void bellman() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            for (int k = 0; k < map[j].size(); k++) {
                int next = map[j][k].first;
                int weight = map[j][k].second;
                if (dist[j] == INF) continue; // 올 수 없는 곳
                if (dist[next] < dist[j] + weight) {
                    dist[next] = dist[j] + weight;
                    pre[next] = j;
                    if (i == n && chk[next])
                        cycle = true;
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> u >> v >> w;
        map[u].push_back({v, w});
        rev[v].push_back(u);
    }

    q.push(n);
    chk[n] = true;
    while (!q.empty()) {
        int idx = q.front();
        q.pop();
        for (int i = 0; i < rev[idx].size(); i++) {
            int next = rev[idx][i];
            if (!chk[next]) {
                chk[next] = true;
                q.push(next);
            }
        }
    }

    init(); // 거리 초기화
    bellman();
    if (cycle) {
        cout << "-1\n";
    } else {
        int idx = n;
        while (1) {
            ans.push_back(idx);
            if (idx == 1)
                break;
            else
                idx = pre[idx];
        }
        for (int i = ans.size() - 1; i >= 0; i--)
            cout << ans[i] << " ";
        cout << '\n';
    }

    return 0;
}