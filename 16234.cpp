#include <iostream>
#include <queue>
#include <cmath>
#include <vector>

using namespace std;
#define MAX 51
int map[MAX][MAX], N, L, R, ans;
int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};
bool been[MAX][MAX];
queue<pair<int, int >> q;
vector<pair<int, int>> countries; // 좌표 x, y, 인구 수

void reset() {
    while (!q.empty())
        q.pop();
    countries.clear();
}

void resetBeen() {
    for (int i = 0; i < MAX; i++)
        for (int j = 0; j < MAX; j++)
            been[i][j] = false;
}

bool isOpen(int populationA, int populationB) {
    int diff = abs(populationA - populationB);
    if (diff >= L && diff <= R)
        return true;
    else
        return false;
}

int bfs(int x, int y) {
    reset();
    q.push({x, y});
    been[y][x] = true;
    int cnt = 0;
    while (!q.empty()) {
        int cx = q.front().first;
        int cy = q.front().second;
        int popA = map[cy][cx];
        q.pop();
        countries.push_back({cx, cy});
        cnt += popA;

        for (int i = 0; i < 4; i++) {
            int nx = cx + dx[i];
            int ny = cy + dy[i];
            if (nx < 0 || nx >= N || ny < 0 || ny >= N) continue;
            if (been[ny][nx]) continue;
            int popB = map[ny][nx];
            if (isOpen(popA, popB)) {
                been[ny][nx] = true;
                q.push({nx, ny});
            }
        }
    }
    cnt /= countries.size();
    for (int i = 0; i < countries.size(); i++) {
        int cx = countries[i].first;
        int cy = countries[i].second;
        map[cy][cx] = cnt;
    }
    if (countries.size() == 1)
        return 0;
    else
        return 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> L >> R;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> map[i][j];

    while (1) {
        int cnt = 0;
        resetBeen();
        for (int i = 0; i < N; i++)
            for (int j = 0; j < N; j++)
                if (!been[i][j])
                    cnt += bfs(j, i);
        if (cnt == 0)
            break;
        ans++;
    }
    cout << ans << '\n';
    return 0;
}