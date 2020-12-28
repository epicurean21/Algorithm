#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;
#define ll long long
#define MAX 101
#define INF 999999999

int N, M, S, E;
int cost[MAX], been[MAX], gv[MAX];
ll dist[MAX];
vector<vector<pair<int, int>>> map(MAX);

void reset() {
    for (int i = 0; i < MAX; i++)
        dist[i] = -INF;
}

void bellman() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < map[j].size(); k++) {
                int next = map[j][k].first;
                int w = map[j][k].second;

                if (dist[j] != -INF && dist[next] < dist[j] - w + cost[next]) {
                    dist[next] = dist[j] - w + cost[next];
                    if (i == N - 1)
                        gv[j] = true;
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> S >> E >> M;
    reset();

    for (int i = 0; i < M; i++) {
        int s, e, w;
        cin >> s >> e >> w;
        map[s].push_back({e, w});
    }

    for (int i = 0; i < N; ++i)
        cin >> cost[i];

    dist[S] = cost[S];
    bellman();

    bool flag = false;
    queue<int> q;

    for (int i = 0; i < N; i++) {
        if (gv[i]) {
            been[i] = true;
            q.push(i);
        }
    }

    while (!q.empty()) {
        int cur = q.front();
        q.pop();

        if (cur == E) {
            flag = true;
            break;
        }

        for (int i = 0; i < map[cur].size(); ++i) {
            int next = map[cur][i].first;
            if (!been[next]) {
                been[next] = true;
                q.push(next);
            }
        }
    }

    if (dist[E] == -INF)
        cout << "gg";
    else if (flag)
        cout << "Gee";
    else
        cout << dist[E];

    return 0;
}