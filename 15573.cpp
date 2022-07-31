/**
 * 15573 채굴
 * 이분탐색, 깊이우선탐색, 그래프이론
 * 구현
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;
#define MAX 1001
int N, M, K, D, S, maxS, minS = INT32_MAX;
int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};
vector<vector<int>> map;
bool visited[MAX][MAX];

void init() {
    memset(visited, false, sizeof(visited));
}

int checkDigable(int size) {
    init();
    int cnt = 0;
    queue<pair<int, int>> q;

    for (int i = 0; i < N; i++) {
        if (map[i][0] <= size) { // 왼쪽 벽
            q.push({0, i});
            visited[i][0] = true;
            cnt++;
        }
        if (map[i][M - 1] <= size) { // 오른쪽 벽
            q.push({M - 1, i});
            visited[i][M - 1] = true;
            cnt++;
        }
    }

    for (int i = 0; i < M; i++) {
        if (map[0][i] <= size && !visited[0][i]) { // 위쪽 벽
            q.push({0, i});
            visited[0][i] = true;
            cnt++;
        }
    }

    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx < 0 || nx >= M || ny < 0 || ny >= N) continue;
            if (visited[ny][nx]) continue;
            if (map[ny][nx] > size) continue;
            visited[ny][nx] = true;
            cnt++;
            q.push({nx, ny});
        }
    }
    return cnt;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> N >> M >> K;
    map.resize(N + 1);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> S;
            map[i].emplace_back(S);
            maxS = max(maxS, S);
            minS = min(minS, S);
        }
    }

    while (minS < maxS) {
        int m = (minS + maxS) >> 1;
        if (checkDigable(m) >= K) {
            D = m;
            maxS = m;
        } else
            minS = m + 1;

    }

    cout << minS << '\n';

    return 0;
}
/*
5 5 10
5 3 10 10 3
4 3 10 10 4
3 4 7 7 3
3 4 4 4 4
3 2 10 4 3
 */