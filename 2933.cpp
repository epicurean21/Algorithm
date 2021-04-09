#include <iostream>
#include <string>
#include <queue>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
#define MAX 102
#define INF 12341
int Y, X, N, shoot[MAX], h;
char map[MAX][MAX];
bool been[MAX][MAX];
int dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};
vector<pair<int, int>> vec;

int min(int a, int b) {
    return a > b ? b : a;
}

int find_min() {
    int min_move = INF;
    bool same_cluster[MAX][MAX];
    memset(same_cluster, false, sizeof(same_cluster));

    for (int i = 0; i < vec.size(); i++) {
        int curx = vec[i].second;
        int cury = vec[i].first;
        same_cluster[cury][curx] = true;
    }

    for (int i = 0; i < vec.size(); i++) {
        int curx = vec[i].second;
        int cury = vec[i].first;

        int tmp = cury;
        while (1) {
            if (map[tmp + 1][curx] == 'x' || tmp == Y) {
                if (same_cluster[tmp + 1][curx]) // 같은 cluster애다
                    break;
                min_move = min(tmp - cury, min_move);
                break;
            }
            tmp++;
        }
    }
    return min_move;
}

void dfs(int x, int y) {
    been[y][x] = true;
    vec.push_back({y, x});

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx < 1 || nx > X || ny < 1 || ny > Y) continue;
        if (been[ny][nx]) continue;
        if (map[ny][nx] == '.') continue;
        been[ny][nx] = true;
        dfs(nx, ny);
    }
}

void move(int height) {
    for (int i = 0; i < vec.size(); i++) {
        int curx = vec[i].second;
        int cury = vec[i].first;

        map[cury][curx] = '.';
        map[cury + height][curx] = 'x';
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> Y >> X;
    for (int i = 1; i <= Y; i++) {
        string str;
        cin >> str;
        for (int j = 1; j <= X; j++)
            map[i][j] = str[j - 1];
    }

    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> h;
        shoot[i] = Y - h + 1;
    }

    for (int i = 0; i < N; i++) {
        int shooting = shoot[i];
        int x = 0;
        bool destroy = true;
        if (i % 2 == 0) { // 왼쪽
            for (int j = 1; j <= X; j++)
                if (map[shooting][j] == 'x') {
                    map[shooting][j] = '.';
                    x = j;
                    destroy = false;
                    break;
                }
        } else { // 오른쪽
            for (int j = X; j >= 1; j--)
                if (map[shooting][j] == 'x') {
                    map[shooting][j] = '.';
                    x = j;
                    destroy = false;
                    break;
                }
        }

        if (destroy) continue;
        for (int j = 0; j < 4; j++) {
            int nx = x + dx[j];
            int ny = shooting + dy[j];

            if (nx <= 0 || nx > X || ny <= 0 || ny > Y) continue;
            if (map[ny][nx] == '.') continue;
            memset(been, false, sizeof(been));
            vec.clear();
            dfs(nx, ny);
            sort(vec.begin(), vec.end(), greater<pair<int, int>>());
            if (vec[0].first == Y) continue;
            int min_move = find_min(); // 최소 움직임 파악
            move(min_move);
        }
    }
    for (int i = 1; i <= Y; i++) {
        for (int j = 1; j <= X; j++)
            cout << map[i][j];
        cout << '\n';
    }
    return 0;
}
/*
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>

using namespace std;
#define LEFT 0
#define RIGHT 1

int r, c, n;
char map[102][102];
vector<pair<bool, int>> attack;
int checkV = 1;
int checkCluster = 1;
int visit[102][102];
int clusterCheck[102][102];
int mx[] = {0, 0, 1, -1};
int my[] = {1, -1, 0, 0};
vector<pair<int, int>> airC;

bool isAir(int x, int y) {
    bool ret = true;
    queue<pair<int, int>> q;
    q.push({x, y});
    airC.push_back({x, y});
    visit[x][y] = checkV;
    clusterCheck[x][y] = checkCluster;
    while (!q.empty()) {
        int curX = q.front().first;
        int curY = q.front().second;
        q.pop();

        if (curX == 1) {
            ret = false;
        }

        for (int i = 0; i < 4; i++) {
            int nextX = curX + mx[i];
            int nextY = curY + my[i];
            if (nextX < 1 || nextX > r || nextY < 1 || nextY > c) continue;
            if (map[nextX][nextY] == '.') continue;
            if (visit[nextX][nextY] == checkV) continue;
            airC.push_back({nextX, nextY});
            visit[nextX][nextY] = checkV;
            clusterCheck[nextX][nextY] = checkCluster;
            q.push({nextX, nextY});
        }
    }
    return ret;
}

void checkDrop() {
    for (int i = 1; i <= r; i++) {
        for (int j = 1; j <= c; j++) {
            if (map[i][j] == 'x' && visit[i][j] != checkV) {
                if (isAir(i, j)) { // 공중에 떠있는 클러스터
                    int maxCanDrop = 1000;
                    for (int k = 0; k < airC.size(); k++) {
                        int canDrop = 0;
                        int f = airC[k].first;
                        int pos = airC[k].second;
                        for (int h = f - 1; h >= 1; h--) {
                            if (map[h][pos] == '.') {
                                canDrop++;
                                if (h == 1) {
                                    maxCanDrop = min(maxCanDrop, canDrop);
                                }
                            } else if (map[h][pos] == 'x') {
                                if (clusterCheck[h][pos] == checkCluster) {
                                    break;
                                }
                                maxCanDrop = min(maxCanDrop, canDrop);
                                break;
                            } else {
                                maxCanDrop = min(maxCanDrop, canDrop);
                                break;
                            }
                        }
                    }
                    for (int k = 0; k < airC.size(); k++) {
                        int f = airC[k].first;
                        int pos = airC[k].second;
                        map[f][pos] = '.';
                    }
                    for (int k = 0; k < airC.size(); k++) {
                        int f = airC[k].first;
                        int pos = airC[k].second;
                        map[f - maxCanDrop][pos] = 'x';
                    }
                    airC.clear();
                } else { // 바닥에 붙어있음
                    airC.clear();
                }
                checkCluster++;
            }
        }
    }
}

int main() {
    cin.tie(NULL);
    ios::sync_with_stdio(false);
    cin >> r >> c;
    for (int i = r; i >= 1; i--) {
        for (int j = 1; j <= c; j++) {
            cin >> map[i][j];
        }
    }
    cin >> n;
    for (int i = 0; i < n; i++) {
        int t;
        cin >> t;
        if (i % 2 == 0) {
            attack.push_back({LEFT, t});
        } else {
            attack.push_back({RIGHT, t});
        }
    }

    for (int i = 0; i < attack.size(); i++) {
        int floor = attack[i].second;
        if (attack[i].first == LEFT) {
            for (int j = 1; j <= c; j++) {
                if (map[floor][j] == 'x') {
                    map[floor][j] = '.';
                    checkDrop();
                    checkV++;
                    break;
                }
            }
        } else if (attack[i].first == RIGHT) {
            for (int j = c; j >= 1; j--) {
                if (map[floor][j] == 'x') {
                    map[floor][j] = '.';
                    checkDrop();
                    checkV++;
                    break;
                }
            }
        }
    }
    for (int i = r; i >= 1; i--) {
        for (int j = 1; j <= c; j++) {
            cout << map[i][j];
        }
        cout << "\n";
    }

    return 0;
}
 */