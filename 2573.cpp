#include <iostream>
#include <queue>

using namespace std;
#define MAX 302

int map[MAX][MAX];
bool been[MAX][MAX];
int N, M, ans;
queue<pair<int, int>> iceberg;
queue<pair<int, int>> tmpIceberg;

int dx[] = { 1, 0, -1, 0 };
int dy[] = { 0, 1, 0, -1 };

void reset() {
    for (int i = 0; i < MAX; i++)
        for (int j = 0; j < MAX; j++)
            been[i][j] = false;
}

void dfs(int x, int y) {
    been[y][x] = true;
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx < 0 || nx >= M || ny < 0 || ny >= N) continue;
        if (map[ny][nx] == 0) continue;
        if (been[ny][nx]) continue;
        int tmp = map[ny][nx];
        dfs(nx, ny);
    }
    return;
}

int cntIceberg() {
    int countingIceberg = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (map[i][j] == 0) continue;
            if (been[i][j]) continue;
            int tmp = map[i][j];
            countingIceberg++;
            dfs(j, i);
        }
    }
    return countingIceberg;
}

int melting() {
    int timeCnt = 0;
    while (cntIceberg() < 2 && !iceberg.empty()) {
        while (!iceberg.empty()) {
            int curx = iceberg.front().second;
            int cury = iceberg.front().first;
            iceberg.pop();
            int cnt = 0;
            for (int i = 0; i < 4; i++) {
                int nx = curx + dx[i];
                int ny = cury + dy[i];
                if (nx < 0 || nx >= M || ny < 0 || ny >= N) continue;
                if (map[ny][nx] != 0) continue; // 빙산
                cnt++;
            }

            map[cury][curx] -= cnt;
            if (map[cury][curx] <= 0)
                map[cury][curx] = -1;

            tmpIceberg.push({ cury, curx });
        }
        while (!tmpIceberg.empty()) {
            if (map[tmpIceberg.front().first][tmpIceberg.front().second] == -1) {
                map[tmpIceberg.front().first][tmpIceberg.front().second] = 0;
                tmpIceberg.pop();
                continue;
            }
            iceberg.push(tmpIceberg.front());
            tmpIceberg.pop();
        }
        timeCnt++;
    }

    if(cntIceberg() < 2)
        return 0;
    return timeCnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> map[i][j];
            if (map[i][j] != 0)
                iceberg.push({ i, j });
        }
    }

    ans = melting();
    cout << ans << "\n";
    return 0;
}