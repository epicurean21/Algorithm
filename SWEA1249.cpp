#include <iostream>
#include <queue>
#include <string>
#include <cstring>
using namespace std;
#define MAX 101
#define INF 9876532
int T, N, map[MAX][MAX];
int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};
int dist[MAX][MAX];
string input;

void bfs() {
    queue<pair<pair<int, int>, int>> q;
    q.push({{0, 0,}, 0});
    while (!q.empty()) {
        int curx = q.front().first.first;
        int cury = q.front().first.second;
        int cost = q.front().second;
        q.pop();
        for (int i = 0; i < 4; i++) {
            int nx = curx + dx[i];
            int ny = cury + dy[i];
            if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
            int nextCost = map[ny][nx] + cost;
            if (dist[ny][nx] <= nextCost) continue;
            dist[ny][nx] = nextCost;
            q.push({{nx, ny}, nextCost});
        }
    }
}

void init() {
    memset(dist, INF, sizeof(dist));
    dist[0][0] = 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> T;
    for (int t = 1; t <= T; t++) {
        cin >> N;
        init();
        for (int i = 0; i < N; i++) {
            cin >> input;
            for (int j = 0; j < input.size(); j++)
                map[i][j] = input[j] - '0';
        }

        bfs();
        cout << "#" << t << " " << dist[N - 1][N - 1] << '\n';
    }
    return 0;
}