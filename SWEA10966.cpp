#include <iostream>
#include <queue>
#include <string>

using namespace std;
#define MAX 1001
int T, N, M, map[MAX][MAX], startX, startY, ans;
int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};
bool chk[MAX][MAX];

void printMap() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++)
            cout << map[i][j] << " ";
        cout << '\n';
    }
}

void init() {
    ans = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            chk[i][j] = false;
}

void bfs(int x, int y) {
    queue<pair<int, int>> q;
    q.push({x, y});
    while (!q.empty()) {
        cout << "\n-------------\n";
        printMap();
        cout << "\n-------------\n";
        int curx = q.front().first;
        int cury = q.front().second;
        q.pop();
        if (map[cury][curx] == -1) { // 물 일때 (W)
            for (int i = 0; i < 4; i++) {
                int nx = curx + dx[i];
                int ny = cury + dy[i];

                if (nx < 0 || nx >= M || ny < 0 || ny >= N) continue;
                if (chk[ny][nx]) continue;
                chk[ny][nx] = true;
                if (map[ny][nx] == -1) {// 물이면
                    q.push({nx, ny});
                    continue;
                } else if (map[ny][nx] == MAX) { // Land, 한번도 안가본곳
                    map[ny][nx] = 1;
                    ans += 1;
                    q.push({nx, ny});
                } else { // Land, 가본 곳
                    ans -= map[ny][nx];
                    map[ny][nx] = 1;
                    ans += 1;
                }
            }
        } else { // 'L' 땅일때
            for (int i = 0; i < 4; i++) {
                int nx = curx + dx[i];
                int ny = cury + dy[i];

                if (nx < 0 || nx >= M || ny < 0 || ny >= N) continue;
                if (map[ny][nx] == -1) {// 물이면
                    ans -= map[cury][curx];
                    map[cury][curx] = 1;
                    ans += 1;
                    q.push({nx, ny});
                } else if (map[ny][nx] == MAX) { // Land, 한번도 안가본곳
                    map[ny][nx] = map[cury][curx] + 1;
                    ans += map[cury][curx] + 1;
                    q.push({nx, ny});
                } else { // Land, 가본 곳
                    if (map[ny][nx] < map[cury][curx] + 1) continue; // 근데 수가 더 작다면 continue
                    ans -= map[ny][nx];
                    ans += map[cury][curx] + 1;
                    map[ny][nx] = map[cury][curx] + 1;
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> T;
    for (int t = 1; t <= T; t++) {
        init();
        cin >> N >> M;
        for (int i = 0; i < N; i++) {
            string str;
            cin >> str;
            for (int j = 0; j < M; j++) {
                if (str[j] == 'W') {
                    map[i][j] = -1;
                    startX = j;
                    startY = i;
                } else if (str[j] == 'L')
                    map[i][j] = MAX;
            }
        }
        bfs(startX, startY);
        cout << "#" << t << " " << ans << '\n';
    }
    return 0;
}


//cout << "\n-------------\n";
//printMap();
//cout << "\n-------------\n";

/*
3
2 3
WLL
LLL
3 2
WL
LL
LW
4 5
LLLWW
WWLLL
LLLWL
LWLLL

4
5 5
WLLWL
LWLLL
LLLLW
WLLLL
LLWLL
2 3
WLL
LLL
3 2
WL
LL
LW
4 5
LLLWW
WWLLL
LLLWL
LWLLL

4
3 3
WWL
LLL
LLW
2 3
WLL
LLL
3 2
WL
LL
LW
4 5
LLLWW
WWLLL
LLLWL
LWLLL

4
2 2
WW
LL
2 3
WLL
LLL
3 2
WL
LL
LW
4 5
LLLWW
WWLLL
LLLWL
LWLLL

 */
