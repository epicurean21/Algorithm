#include <iostream>
#include <string>
#include <queue>

using namespace std;
#define MAX 51

int R, C;
pair<int, int> startPos, endPos;
queue<pair<int, int>> water;
queue<pair<int, int>> waterTmp;
char map[MAX][MAX];
int ans[MAX][MAX];
int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};

void bfs(int x, int y, int cnt) {
    queue<pair<pair<int, int>, int>> pos;
    pos.push({{x, y}, cnt});
    while (!pos.empty()) {
        while (!water.empty()) {
            int waterX = water.front().first;
            int waterY = water.front().second;
            water.pop();

            for (int i = 0; i < 4; i++) {
                int nx = waterX + dx[i];
                int ny = waterY + dy[i];
                if (nx < 0 || nx >= C || ny < 0 || ny >= R) continue;
                if (map[ny][nx] == 'X' || map[ny][nx] == '*' || map[ny][nx] == 'D' || map[ny][nx] == 'S') continue;
                if (ans[ny][nx]) continue;
                map[ny][nx] = '*';
                waterTmp.push({nx, ny});
            }
        }
        while (!waterTmp.empty()) {
            water.push(waterTmp.front());
            waterTmp.pop();
        }

        int curSize = pos.size();
        for (int s = 0; s < curSize; s++) {
            int curx = pos.front().first.first;
            int cury = pos.front().first.second;
            int curCnt = pos.front().second;
            pos.pop();
            ans[cury][curx] = curCnt;
            for (int i = 0; i < 4; i++) {
                int nx = curx + dx[i];
                int ny = cury + dy[i];
                int ncnt = curCnt + 1;

                if (nx < 0 || nx >= C || ny < 0 || ny >= R) continue;
                if (map[ny][nx] == '*' || map[ny][nx] == 'X') continue;
                if (ans[ny][nx]) continue;
                ans[ny][nx] = ncnt;
                pos.push({{nx, ny}, ncnt});
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> R >> C;
    for (int i = 0; i < R; i++) {
        string tmp;
        cin >> tmp;
        for (int j = 0; j < tmp.length(); j++) {
            map[i][j] = tmp[j];
            if (tmp[j] == 'D')
                endPos = {j, i};
            else if (tmp[j] == 'S')
                startPos = {j, i};
            else if (tmp[j] == '*')
                water.push({j, i});
        }
    }

    bfs(startPos.first, startPos.second, 0);
    if (ans[endPos.second][endPos.first])
        cout << ans[endPos.second][endPos.first] << "\n";
    else
        cout << "KAKTUS\n";
    return 0;
}