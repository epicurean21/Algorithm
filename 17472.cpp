#include <iostream>
#include <queue>
#include <vector>
#include <cstring>

using namespace std;
#define MAX 11
#define INF 1001
#define ISLANDMAX 7
int N, M, map[MAX][MAX], ans = INF, dist[ISLANDMAX][ISLANDMAX], label[MAX][MAX];
int islandCnt, dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};
vector<pair<int, int>> v; // 모든 땅의 좌표
vector<pair<int, int>> islandIdx[MAX]; // 각 섬별로의 좌표 저장
vector<pair<pair<int, int>, int>> edge; // 모든 다
bool chk[MAX][MAX];
bool Connect[ISLANDMAX][ISLANDMAX];    // 연결관계 체크를 위한 배열
bool ConnectIsland[ISLANDMAX];            // BFS탐색 시, 방문체크를 위한 배열(연결관계를 통해, 정답을 도출하기 위한 BFS탐색 시 사용)
bool Select[ISLANDMAX * ISLANDMAX];

void bfs(int x, int y, int num) {
    queue<pair<int, int>> q;
    q.push({x, y});
    chk[y][x] = true;
    label[y][x] = num;
    islandIdx[num].push_back({x, y});

    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 0 && nx < M && ny >= 0 && ny < N) {
                if (!chk[ny][nx] && map[ny][nx] == 1) {
                    chk[ny][nx] = true;
                    label[ny][nx] = num;
                    q.push({nx, ny});
                    islandIdx[num].push_back({nx, ny});
                }
            }
        }
    }
}

void numberIsland() {
    int tmp = 1;
    for (int i = 0; i < v.size(); i++) {
        int x = v[i].first;
        int y = v[i].second;
        if (!chk[y][x])
            bfs(x, y, tmp++);
    }
    islandCnt = tmp;
}

void dfs(int x, int y, int dir, int sz, int start, int end) {
    int nx = x + dx[dir];
    int ny = y + dy[dir];
    if (nx < 0 || nx >= M || ny < 0 || ny >= N) return;
    if (map[ny][nx] == 0)
        dfs(nx, ny, dir, sz + 1, start, end);
    else if (map[ny][nx] == 1) { // 탐색중 정점이 땅
        if (label[ny][nx] == end) { // 도착섬에 도착했다면
            if (sz > 1) {
                if (dist[start][end] > sz) { // 길이 갱신
                    dist[start][end] = sz;
                    dist[end][start] = sz;
                }
                return;
            }
        }
        return;
    }
}

void makeCon(int start, int end) {
    for (int i = 0; i < islandIdx[start].size(); i++) {
        int x = islandIdx[start][i].first;
        int y = islandIdx[start][i].second;

        for (int j = 0; j < 4; j++) {
            int nx = x + dx[j];
            int ny = y + dy[j];
            if (nx >= 0 && ny >= 0 && ny < N && nx < M)
                if (map[ny][nx] == 0)
                    dfs(x, y, j, 0, start, end);
        }
    }
}

void findDist() {
    for (int i = 1; i < islandCnt; i++) {
        for (int j = i + 1; j < islandCnt; j++) {
            makeCon(i, j);
            if (dist[i][j] == INF) continue;
            edge.push_back({{j, i}, dist[i][j]});
        }
    }
}

bool CheckState() {
    memset(Connect, false, sizeof(Connect));
    memset(ConnectIsland, false, sizeof(ConnectIsland));
    for (int i = 0; i < edge.size(); i++) {
        if (Select[i] == true) {
            int x = edge[i].first.first;
            int y = edge[i].first.second;

            Connect[x][y] = true;    // 선택한 다리가 연결하는 섬들의 연결관계를 표시
            Connect[y][x] = true;
        }
    }

    // 이후 BFS탐색을 통해서 탐색할 수 있는 섬의 갯수를 Count.
    queue<int> Q;
    Q.push(1);
    ConnectIsland[1] = true;

    int IslandCnt = 1;
    bool Flag = false;
    while (Q.empty() == 0) {
        int Cur = Q.front();
        Q.pop();

        if (IslandCnt == islandCnt - 1) {
            Flag = true;
            break;
        }

        for (int i = 1; i < islandCnt; i++) {
            if (Cur == i) continue;
            if (Connect[Cur][i] == true && ConnectIsland[i] == false) {
                ConnectIsland[i] = true;
                Q.push(i);
                IslandCnt++;
            }
        }
    }
    return Flag;
}

void findAns(int idx, int cnt, int sum) {
    if (cnt >= 1)
        if (CheckState())
            if (ans > sum)
                ans = sum;
    for (int i = idx; i < edge.size(); i++) {
        if (Select[i])
            continue;
        Select[i] = true;
        findAns(i, cnt + 1, sum + edge[i].second);
        Select[i] = false;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    memset(dist, INF, sizeof(dist));
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> map[i][j];
            if (map[i][j] == 1)
                v.push_back({j, i});
        }
    }
    numberIsland();
    findDist();
    findAns(0, 0, 0);
    if (ans == INF)
        cout << "-1\n";
    else
        cout << ans << '\n';
    return 0;
}

#include<iostream>
#include<vector>
#include<queue>
#include<memory.h>
#include<algorithm>

using namespace std;
const int MAX = 12;

int n, m;
int arr[MAX][MAX];
int map[MAX][MAX];
bool check[MAX][MAX];

struct coor {
    int y;
    int x;
    int num;
};
queue<coor> q, bq;

int gNum = 1;

bool inside(int y, int x) {
    return y >= 0 && y < n && x >= 0 && x < m;
}
int dy[] = {-1, 1, 0, 0};
int dx[] = {0, 0, -1, 1};

struct bridge {
    int a;
    int b;
    int c;
};
vector<bridge> v;

bool cmp(const bridge &a, const bridge &b) {
    if (a.c < b.c) return true;
    else return false;
}
int p[102];

void bfs() {
    while (!q.empty()) {
        int y = q.front().y;
        int x = q.front().x;
        int num = q.front().num;
        q.pop();

        int ny, nx;
        for (int i = 0; i < 4; i++) {
            ny = y + dy[i];
            nx = x + dx[i];
            if (inside(ny, nx) && check[ny][nx] == 0 && arr[ny][nx] == 1) {
                check[ny][nx] = 1;
                map[ny][nx] = num;
                q.push({ny, nx, num});
                bq.push({ny, nx, num});
            }
        }
    }
}

int find(int x) {
    if (p[x] == x) return x;
    else return p[x] = find(p[x]);
}

void Union(int a, int b) {
    a = find(a);
    b = find(b);
    p[a] = b;
}

bool sp(int a, int b) {
    a = find(a);
    b = find(b);
    if (a != b) return false;
    else return true;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    // 1. input
    memset(check, 0, sizeof(check));
    cin >> n >> m;
    for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) cin >> arr[i][j];

    // 2. 섬 번호 메기기
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (arr[i][j] == 1 && check[i][j] == 0) {
                check[i][j] = 1;
                map[i][j] = gNum;
                q.push({i, j, gNum});
                bq.push({i, j, gNum});
                bfs();
                gNum++;
            }
        }
    }

    // 3. 섬에서 다른 섬 갈 수 있는지 확인하고,
    // vector에 (섬1 , 섬2 , 거리) 로 넣기
    memset(check, 0, sizeof(check));
    while (!bq.empty()) {
        int y = bq.front().y;
        int x = bq.front().x;
        int num = bq.front().num;
        bq.pop();

        int ny, nx;
        for (int i = 0; i < 4; i++) {
            int s = 1;
            int cnt = 1;
            while (true) {
                ny = y + dy[i] * s;
                nx = x + dx[i] * s;
                if (!inside(ny, nx)) break;
                if (map[ny][nx] == num) break;
                if (map[ny][nx] != 0 && map[ny][nx] != num) {
                    if (cnt - 1 >= 2) v.push_back({num, map[ny][nx], cnt - 1});
                    break;
                }
                s++;
                cnt++;
            }
        }
    }

    for (int i = 1; i < 102; i++)
        p[i] = i;
    sort(v.begin(), v.end(), cmp);
    int ans = 0;
    vector<int> c[7];
    bool check2[102] = {0,};
    queue<int> lq;
    int m = 0;
    for (int i = 0; i < v.size(); i++) {
        if (sp(v[i].a, v[i].b) == false) {
            Union(v[i].a, v[i].b);
            ans += v[i].c;
            c[v[i].a].push_back(v[i].b);
            c[v[i].b].push_back(v[i].a);
            if (m == 0) m = v[i].a;
        }
    }

    lq.push(m);
    while (!lq.empty()) {
        int num = lq.front();
        lq.pop();
        check2[num] = true;
        for (int i = 0; i < c[num].size(); i++) {
            if (check2[c[num][i]] == false) {
                check2[c[num][i]] = true;
                lq.push(c[num][i]);
            }
        }
    }

    bool flag = false;
    for (int i = 1; i < gNum; i++)
        if (check2[i] == false)
            flag = true;

    if (flag == false)
        cout << ans << "\n";
    else cout << "-1\n";
    return 0;
}