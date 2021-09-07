/**
 * 9376 탈옥
 * 그래프, DFS
 * 다익스트라
 * (. 빈공간, * 벽, # 문, $ 죄수)
 * 최소의 문을 열어서 탈출시켜야한다.
 * 한놈이 탈출했을 때, 해당 경로로 다른놈이 탈출 할 수 있는지 확인 ?
 * 단순 계산으론 안될듯..
 * 음 두 죄수가 만날 수 있는 점을 찾아서 밖으로 나가는 길의 최솟값
 *
 * 죄수 둘이 만나는 지점이 생기면 그때가 탈출한경우. 즉 최소로 만나는 위치까지 문을 부신 수 ?
 */

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <cstring>

using namespace std;
#define MAX 102

int tc, h, w, ans;
int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1}, dist[3][MAX][MAX];
bool chk[MAX][MAX];
vector<pair<int, int>> prisoners;
char map[MAX][MAX];
priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<>> pq;

void print_map(int H, int W) {
    cout << "\n----------print map----------\n";
    for (int i = 0; i <= H + 1; i++) {
        for (int j = 0; j <= W + 1; j++)
            cout << map[i][j];
        cout << '\n';
    }
    cout << '\n';
}

int min(int a, int b) {
    return a > b ? b : a;
}

void init(int H, int W) {
    for (int i = 0; i <= H + 1; i++)
        for (int j = 0; j <= W + 1; j++)
            map[i][j] = '.';
    prisoners.clear();
    prisoners.emplace_back(0, 0); // 상근이가 0,0 에 있다고 하자

    for (int i = 0; i < 3; i++)
        for (int j = 0; j <= H + 1; j++)
            for (int k = 0; k <= W + 1; k++)
                dist[i][j][k] = INT32_MAX;

    ans = INT32_MAX;
    while (!pq.empty())
        pq.pop();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tc;

    while (tc--) {
        cin >> h >> w;

        init(h, w);

        for (int i = 1; i <= h; i++) {
            string input;
            cin >> input;
            for (int j = 1; j <= w; j++) {
                map[i][j] = input[j - 1];
                if (input[j - 1] == '$')
                    prisoners.emplace_back(j, i); // 죄수 x, y 좌표
            }
        }

        //print_map(h, w);

        for (int i = 0; i < 3; i++) {
            pq.push({0, {prisoners[i]}});
            dist[i][prisoners[i].second][prisoners[i].first] = 0;
            memset(chk, false, sizeof(chk));

            while (!pq.empty()) {
                int x = pq.top().second.first;
                int y = pq.top().second.second;
                int cost = pq.top().first;

                pq.pop();

                for (int j = 0; j < 4; j++) {
                    int nx = x + dx[j];
                    int ny = y + dy[j];
                    int next_cost = cost;

                    if (nx < 0 || nx > w + 1 || ny < 0 || ny > h + 1) continue;
                    if (chk[ny][nx]) continue; // 이미 방문
                    if (map[ny][nx] == '*') continue; // 벽

                    if (map[ny][nx] == '#')
                        next_cost++;

                    if (next_cost < dist[i][ny][nx]) {
                        dist[i][ny][nx] = next_cost;
                        chk[ny][nx] = true;
                        pq.push({next_cost, {nx, ny}});
                    }
                }
            }
        }

        for (int i = 1; i <= h; i++) {
            for (int j = 1; j <= w; j++) {
                if (map[i][j] == '*') continue;
                int tmp = 0;
                for (int k = 0; k < 3; k++)
                    tmp += dist[k][i][j];
                if (map[i][j] == '#') tmp -= 2;

                ans = min(ans, tmp);
            }
        }

        cout << ans << '\n';
    }
    return 0;
}