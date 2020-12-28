#include <iostream>
#include <queue>

using namespace std;
#define maxN 1002
int N, K, S, X, Y;
int map[maxN][maxN];
priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;
queue<pair<int, pair<int, int>>> q;
int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};
bool chk[maxN][maxN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> K;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> map[i][j];
            if (!map[i][j]) continue;
            chk[i][j] = true;
            pq.push({map[i][j], {i, j}});
        }
    }
    cin >> S >> X >> Y;
    for (int k = 0; k < S; k++) {
        while (!pq.empty()) {
            int cur = pq.top().first;
            int x = pq.top().second.second;
            int y = pq.top().second.first;
            pq.pop();
            for (int i = 0; i < 4; i++) {
                int nx = x + dx[i];
                int ny = y + dy[i];
                if (nx < 0 || nx >= K || ny < 0 || ny >= N) continue;
                if (chk[ny][nx]) continue;
                map[ny][nx] = cur;
                chk[ny][nx] = true;
                q.push({cur, {ny, nx}});
            }
        }
        while (!q.empty()) {
            pq.push(q.front());
            q.pop();
        }
    }
    cout << map[X - 1][Y - 1] << "\n";
    return 0;
}