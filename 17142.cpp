#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;
#define MAX 52
#define INF 123456
int N, M, idx, ans = INF + 1, dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};
int timeMap[MAX][MAX], map[MAX][MAX];
bool been[MAX][MAX];
vector<pair<int, int>> viruses;

int max(int a, int b) { return a > b ? a : b; }

int min(int a, int b) { return a > b ? b : a; }

int timeCost() {
    int tmp = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (timeMap[i][j] == -1) continue; // 벽임
            if(map[i][j] == -2) continue; // 바이러스임
            if (timeMap[i][j] == 0 && map[i][j] != -2) return INF; // 즉 바이러스 시작 위치가 아닌데 0 이다? 못 간곳
            tmp = max(tmp, timeMap[i][j]);
        }
    }
    return tmp;
}

void BFS(int x, int y) {
    queue<pair<pair<int, int>, int>> q;
    q.push({{x, y}, 0});
    while (!q.empty()) {
        int cx = q.front().first.first;
        int cy = q.front().first.second;
        int cnt = q.front().second;
        q.pop();
        been[cy][cx] = true;
        timeMap[cy][cx] = cnt;

        for (int i = 0; i < 4; i++) {
            int nx = cx + dx[i];
            int ny = cy + dy[i];
            if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
            if (map[ny][nx] == -1) continue; // 벽 이거나 바이러스 위치임
            if (been[ny][nx]) continue;
            if (timeMap[ny][nx] != 0 && timeMap[ny][nx] < cnt + 1 && map[ny][nx] != -2) continue; // 0이 아닌데 그 값이 내 턴보다 작다;
            been[ny][nx] = true;
            q.push({{nx, ny}, cnt + 1});
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> map[i][j];
            if (map[i][j] == 2) {
                viruses.push_back({j, i});
                map[i][j] = -2;
                idx++;
            }
            if (map[i][j] == 1)
                map[i][j] = -1;
        }
    }
    vector<int> perm(idx);
    for (int i = 0; i < idx - M; i++)
        perm[i] = 0;
    for (int i = idx - M; i < idx; i++)
        perm[i] = 1;

    do {
        memcpy(timeMap, map, sizeof(map));
        for (int i = 0; i < viruses.size(); i++) {
            if (perm[i] == 1) { // 해당한 것만 BFS를 돌린다
                memset(been, false, sizeof(been));
                int vx = viruses[i].first;
                int vy = viruses[i].second;
                BFS(vx, vy);
            }
        }
        ans = min(ans, timeCost());
    } while (next_permutation(perm.begin(), perm.end()));
    if (ans == INF)
        cout << "-1\n";
    else
        cout << ans << '\n';
    return 0;
}