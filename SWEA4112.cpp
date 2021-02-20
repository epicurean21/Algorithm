#include <iostream>
#include <queue>
#include <cstring>

using namespace std;
#define MAX 10010
#define INF 987654
int T, a, b;
int dist[MAX], level[MAX], chk[MAX];

void bfs(int cur, int end) {
    dist[cur] = 0;
    queue<pair<int, int>> q;
    q.push({cur, 0});
    while (!q.empty()) {
        int now = q.front().first;
        int cnt = q.front().second;
        chk[now] = true;
        q.pop();
        if (now == end)
            break;
        if (now > end) { // 더 크다, 즉 위로 올라가야한다
            int next;
            for (int i = 1; i <= 4; i++) {
                if (i == 1) {
                    next = now - 1;
                    if (next <= 0) continue;
                    if (level[next] != level[now]) continue;
                } else if (i == 2) {
                    next = now - level[now];
                    if (next <= 0) continue;
                    if (level[next] != level[now] - 1) continue;
                } else if (i == 3) {
                    if (end > cur) continue;
                    next = now - level[now] + 1;
                    if (next <= 0) continue;
                    if (level[next] != level[now] - 1) continue;
                } else if (i == 4) {
                    next = now + 1;
                    if (level[next] != level[now])
                        continue;
                }
                if (chk[next]) continue;
                chk[next] = true;
                if (dist[next] < cnt + 1) continue;
                dist[next] = cnt + 1;
                q.push({next, cnt + 1});
            }
        } else {
            int next;
            for (int i = 1; i <= 4; i++) {
                if (i == 1) {
                    next = now - 1;
                    if (level[next] != level[now]) continue;
                } else if (i == 2) {
                    next = now + level[now];
                    if (next > 10000) continue;
                } else if (i == 3) {
                    next = now + level[now] + 1;
                    if (next > 10000) continue;
                } else if (i == 4) {
                    next = now + 1;
                    if (next > 10000) continue;
                    if (level[next] != level[now])
                        continue;
                }
                if (chk[next]) continue;
                chk[next] = true;
                if (dist[next] < cnt + 1)
                    continue;
                dist[next] = cnt + 1;
                q.push({next, cnt + 1});
            }
        }
    }
}

void saveLevel() {
    int idx = 1;
    for (int i = 1; i <= 142; i++)
        for (int j = 1; j <= i; j++)
            level[idx++] = i;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    saveLevel();
    cin >> T;
    for (int t = 1; t <= T; t++) {
        memset(dist, INF, sizeof(dist));
        memset(chk, false, sizeof(chk));
        cin >> a >> b;
        //cout << level[a] << " " << level[b] << '\n';
        if (a == b) {
            cout << "#" << t << " 0\n";
            continue;
        }

        bfs(a, b);
        cout << "#" << t << " " << dist[b] << "\n";
    }
    return 0;
}