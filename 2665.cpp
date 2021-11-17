/**
 * 2665 미로만들기
 * 너비우선탐색, Dijkstra
 * 전형적인 Dijkstra 문제이다
 * 다만 Vertex 간의 edge의 길이에 따른 최단 경로가 아닌
 * 인접한 방으로 이동할 때 까지 벽을 부순 횟수의 최소값으로 이동하면된다.
 */

#include <iostream>
#include <string>
#include <queue>

using namespace std;
#define MAX 51
int n, map[MAX][MAX], cnt[MAX][MAX], dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};
string input;
priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;

void init() {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cnt[i][j] = INT32_MAX;
}

void print_cnt() {
    cout << "------------print cnt------------\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            cout << cnt[i][j] << " ";
        cout << "\n";
    }
    cout << '\n';
}

void dijkstra(int sx, int sy, int dist) {
    cnt[sy][sx] = 0;
    pq.push({dist, {sx, sy}});

    while (!pq.empty()) {
        int x = pq.top().second.first;
        int y = pq.top().second.second;
        int count = pq.top().first;
        pq.pop();

        print_cnt();

        if (cnt[y][x] < count) continue;

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;

            int n_count = map[ny][nx] == 1 ? count : count + 1;

            if (cnt[ny][nx] > n_count) {
                cnt[ny][nx] = n_count;
                pq.push({n_count, {nx, ny}});
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    init();

    for (int i = 0; i < n; i++) {
        cin >> input;
        for (int j = 0; j < n; j++)
            map[i][j] = input[j] - '0';
    }

    dijkstra(0, 0, 0);
    cout << cnt[n - 1][n - 1];
    return 0;
}