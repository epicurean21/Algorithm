/**
 * 13913 숨바꼭질 2
 * 그래프 이론
 */

#include <iostream>
#include <queue>

using namespace std;
#define MAX 100001
int N, K, cnt;// N: 수빈 위치, K: 동생 위치. N -> K의 최단경로, X-1 || X+1 || 2*X
pair<int, int> map[MAX]; // <걸린 시간, 오게된 위치>

void init() {
    for (int i = 0; i < MAX; i++)
        map[i].first = INT32_MAX;
}

void bfs(int start) {
    queue<pair<int, int>> points;
    points.push({start, 0});
    map[start].first = 0;
    map[start].second = -1;

    while (!points.empty()) {
        int cur = points.front().first;
        int time = points.front().second;
        points.pop();

        if (cur == K)
            cnt++;

        int walk1 = cur - 1;
        int walk2 = cur + 1;
        int teleport = cur * 2;
        if (walk1 >= 0 && map[walk1].first >= time + 1 && walk1 != start) {
            map[walk1].first = time + 1;
            map[walk1].second = cur;
            points.push({walk1, time + 1});
        }
        if (walk2 >= 0 && map[walk2].first >= time + 1 && walk2 != start && walk2 < MAX) {
            map[walk2].first = time + 1;
            map[walk2].second = cur;
            points.push({walk2, time + 1});
        }
        if (teleport < MAX && map[teleport].first >= time + 1 && teleport != start) {
            map[teleport].first = time + 1;
            map[teleport].second = cur;
            points.push({teleport, time + 1});
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> K;
    init();
    bfs(N);
    cout << map[K].first << "\n" << cnt << "\n";

    return 0;
}