#include <iostream>
#include <queue>
#include <vector>

using namespace std;
#define MAX 204
#define INF 12345
int N, M, fuel, map[MAX][MAX], taxiX, taxiY;
int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};
queue<pair<pair<int, int>, int>> q;
vector<pair<pair<int, int>, pair<int, int>>> customers(MAX * MAX); // 출발지 목적지
queue<pair<pair<int, int>, int>> bfs;
bool finished[MAX * MAX]; // 완료한 고객
bool been[MAX][MAX];

int min(int a, int b) {
    return a > b ? b : a;
}

void reset() {
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            been[i][j] = false;
        }
    }
    while (!bfs.empty()) {
        bfs.pop();
    }
}

int toCustomer(int distX, int distY) {
    reset();
    if (taxiX == distX && taxiY == distY) return 0; // 택시위치 == 손님 위치
    bfs.push({{taxiX, taxiY}, 0});

    while (!bfs.empty()) {
        int cx = bfs.front().first.first;
        int cy = bfs.front().first.second;
        int dist = bfs.front().second;
        bfs.pop();
        been[cy][cx] = true;
        for (int i = 0; i < 4; i++) {
            int nx = cx + dx[i];
            int ny = cy + dy[i];
            int nextDist = dist + 1;
            if (nx <= 0 || nx > N || ny <= 0 || ny > N) continue;
            if (map[ny][nx] == 1) continue;
            if (been[ny][nx]) continue;
            been[ny][nx] = true;
            if (nx == distX && ny == distY) { // 목적지 도착
                return nextDist;
            }
            bfs.push({{nx, ny}, nextDist});
        }
    }

    return -1; // 다 돌았는데 목적지 도착을 못함
}

// 승객끼리 목적지가 같을 수 있다
int toDestination(int customerIdx) {
    reset();
    if (taxiX == customers[customerIdx].second.first
        && taxiY == customers[customerIdx].second.second)
        return 0;

    bfs.push({{taxiX, taxiY}, 0});

    while (!bfs.empty()) {
        int cx = bfs.front().first.first;
        int cy = bfs.front().first.second;
        int dist = bfs.front().second;
        bfs.pop();
        been[cy][cx] = true;
        for (int i = 0; i < 4; i++) {
            int nx = cx + dx[i];
            int ny = cy + dy[i];
            int nextDist = dist + 1;
            if (nx <= 0 || nx > N || ny <= 0 || ny > N) continue;
            if (map[ny][nx] == 1) continue;
            if (been[ny][nx]) continue;
            been[ny][nx] = true;

            if (nx == customers[customerIdx].second.first
                && ny == customers[customerIdx].second.second)  // 목적지 도착
                return nextDist;

            bfs.push({{nx, ny}, nextDist});
        }
    }

    return -1; // 다 돌았는데 목적지 도착을 못함
}

int findNearest() {
    int idx = 1;
    int minDist = INF;
    for (int i = 2; i < M + 2; i++) {
        if (!finished[i]) { // 아직 도착 안한 손님이라면
            int cx = customers[i].first.first; // 손님 x좌표
            int cy = customers[i].first.second; // y 좌표
            int dist = toCustomer(cx, cy); // 택시 위치에서 손님까지 거리 계산
            if (dist == -1) return -1; // 해당 손님한테 갈 수 없다

            if (dist <= minDist) {
                if (dist == minDist) { // 거리가 같은사람 등장 두두등장
                    int dx = customers[idx].first.first; // 이전 가까운 거리의 고객
                    int dy = customers[idx].first.second;
                    if (cy < dy) { // 행이 더 작음
                        minDist = dist;
                        idx = i;
                    } else if (cy == dy) { // 행이 같음,
                        if (cx < dx) { // 열이 작음
                            minDist = dist;
                            idx = i;
                        }
                    }
                } else { // 다음 고객 거리가 지금까지 계산한것보다 짧다
                    minDist = dist;
                    idx = i;
                }
            }
        }
    }

    return idx;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M >> fuel;
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            cin >> map[i][j];

    cin >> taxiY >> taxiX;
    for (int i = 2; i < M + 2; i++) {
        int cx, cy, distX, distY;
        cin >> cy >> cx >> distY >> distX;
        customers[i] = {{cx,    cy},
                        {distX, distY}}; // 목적지, 도착지
    }

    int nextCustomer = findNearest();
    if (nextCustomer == 1 || nextCustomer == -1) {
        cout << "-1\n";
        return 0;
    }

    int nextCustomerX = customers[nextCustomer].first.first;
    int nextCustomerY = customers[nextCustomer].first.second;
    q.push({{nextCustomerX, nextCustomerY}, nextCustomer});

    bool fail = false;
    while (!q.empty()) { // 사람을 다 목적지에 데려다줄 때까지
        int nx = q.front().first.first;
        int ny = q.front().first.second;
        int idx = q.front().second; // 손님 번호
        q.pop();

        int cost = toCustomer(nx, ny); // 손님한테 이동함

        if (cost == -1 || fuel - cost < 0) { // 태우러 못 가던가, 아니면 태우러 갔는데 연료 떨어지던가
            fail = true;
            break;
        }

        taxiX = nx;
        taxiY = ny; // 택시 위치 이동
        fuel -= cost; // 남은 연료 계산

        cost = toDestination(idx); // 목적지로 이동

        if (cost == -1 || fuel - cost < 0) { // 목적지까지 갈 수 없거나, 도착전에 연료 떨어짐
            fail = true;
            break;
        }

        pair<int, int> nextTaxi = customers[idx].second; // 목적지 도착
        taxiX = nextTaxi.first;
        taxiY = nextTaxi.second;
        fuel -= cost;

        finished[idx] = true; // 목적지 델따 줬음 끝 ~
        fuel += cost * 2;
        nextCustomer = findNearest();
        if (nextCustomer == 1) { // 다음 손님 없음
            break;
        } else if (nextCustomer == -1) {
            fail = true;
            break;
        }

        nextCustomerX = customers[nextCustomer].first.first;
        nextCustomerY = customers[nextCustomer].first.second;
        q.push({{nextCustomerX, nextCustomerY}, nextCustomer});
    }

    if (fail)
        cout << "-1\n";
    else {
        cout << fuel << '\n';
    }
    return 0;
}
/*
20 400 500000
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
17 14
1 1 5 5
1 2 5 5
1 3 5 5
1 4 5 5
1 5 5 5
1 6 5 5
1 7 5 5
1 8 5 5
1 9 5 5
1 10 5 5
1 11 5 5
1 12 5 5
1 13 5 5
1 14 5 5
1 15 5 5
1 16 5 5
1 17 5 5
1 18 5 5
1 19 5 5
1 20 5 5
2 1 5 5
2 2 5 5
2 3 5 5
2 4 5 5
2 5 5 5
2 6 5 5
2 7 5 5
2 8 5 5
2 9 5 5
2 10 5 5
2 11 5 5
2 12 5 5
2 13 5 5
2 14 5 5
2 15 5 5
2 16 5 5
2 17 5 5
2 18 5 5
2 19 5 5
2 20 5 5
3 1 5 5
3 2 5 5
3 3 5 5
3 4 5 5
3 5 5 5
3 6 5 5
3 7 5 5
3 8 5 5
3 9 5 5
3 10 5 5
3 11 5 5
3 12 5 5
3 13 5 5
3 14 5 5
3 15 5 5
3 16 5 5
3 17 5 5
3 18 5 5
3 19 5 5
3 20 5 5
4 1 5 5
4 2 5 5
4 3 5 5
4 4 5 5
4 5 5 5
4 6 5 5
4 7 5 5
4 8 5 5
4 9 5 5
4 10 5 5
4 11 5 5
4 12 5 5
4 13 5 5
4 14 5 5
4 15 5 5
4 16 5 5
4 17 5 5
4 18 5 5
4 19 5 5
4 20 5 5
5 1 5 5
5 2 5 5
5 3 5 5
5 4 5 5
5 5 5 6
5 6 5 5
5 7 5 5
5 8 5 5
5 9 5 5
5 16 5 5
5 10 5 5
5 11 5 5
5 12 5 5
5 13 5 5
5 14 5 5
5 15 5 5
5 17 5 5
5 18 5 5
5 19 5 5
5 20 5 5
6 1 5 5
6 2 5 5
6 3 5 5
6 4 5 5
6 5 5 5
6 6 5 5
6 7 5 5
6 8 5 5
6 9 5 5
6 10 5 5
6 11 5 5
6 12 5 5
6 13 5 5
6 14 5 5
6 15 5 5
6 16 5 5
6 17 5 5
6 18 5 5
6 19 5 5
6 20 5 5
7 1 5 5
7 2 5 5
7 3 5 5
7 4 5 5
7 5 5 5
7 6 5 5
7 7 5 5
7 8 5 5
7 9 5 5
7 10 5 5
7 11 5 5
7 12 5 5
7 13 5 5
7 14 5 5
7 15 5 5
7 16 5 5
7 17 5 5
7 18 5 5
7 19 5 5
7 20 5 5
8 1 5 5
8 2 5 5
8 3 5 5
8 4 5 5
8 5 5 5
8 6 5 5
8 7 5 5
8 8 5 5
8 9 5 5
8 10 5 5
8 11 5 5
8 12 5 5
8 13 5 5
8 14 5 5
8 15 5 5
8 16 5 5
8 17 5 5
8 18 5 5
8 19 5 5
8 20 5 5
9 1 5 5
9 2 5 5
9 3 5 5
9 4 5 5
9 5 5 5
9 6 5 5
9 7 5 5
9 8 5 5
9 9 5 5
9 10 5 5
9 11 5 5
9 12 5 5
9 13 5 5
9 14 5 5
9 15 5 5
9 16 5 5
9 17 5 5
9 18 5 5
9 19 5 5
9 20 5 5
10 1 5 5
10 2 5 5
10 3 5 5
10 4 5 5
10 5 5 5
10 6 5 5
10 7 5 5
10 8 5 5
10 9 5 5
10 10 5 5
10 11 5 5
10 12 5 5
10 13 5 5
10 14 5 5
10 15 5 5
10 16 5 5
10 17 5 5
10 18 5 5
10 19 5 5
10 20 5 5
11 1 5 5
11 2 5 5
11 3 5 5
11 4 5 5
11 5 5 5
11 6 5 5
11 7 5 5
11 8 5 5
11 9 5 5
11 10 5 5
11 11 5 5
11 12 5 5
11 13 5 5
11 14 5 5
11 15 5 5
11 16 5 5
11 17 5 5
11 18 5 5
11 19 5 5
11 20 5 5
12 1 5 5
12 2 5 5
12 3 5 5
12 4 5 5
12 5 5 5
12 6 5 5
12 7 5 5
12 8 5 5
12 9 5 5
12 10 5 5
12 11 5 5
12 12 5 5
12 13 5 5
12 14 5 5
12 15 5 5
12 16 5 5
12 17 5 5
12 18 5 5
12 19 5 5
12 20 5 5
13 1 5 5
13 2 5 5
13 3 5 5
13 4 5 5
13 5 5 5
13 6 5 5
13 7 5 5
13 8 5 5
13 9 5 5
13 10 5 5
13 11 5 5
13 12 5 5
13 13 5 5
13 14 5 5
13 15 5 5
13 16 5 5
13 17 5 5
13 18 5 5
13 19 5 5
13 20 5 5
14 1 5 5
14 2 5 5
14 3 5 5
14 4 5 5
14 5 5 5
14 6 5 5
14 7 5 5
14 8 5 5
14 9 5 5
14 10 5 5
14 11 5 5
14 12 5 5
14 13 5 5
14 14 5 5
14 15 5 5
14 16 5 5
14 17 5 5
14 18 5 5
14 19 5 5
14 20 5 5
15 1 5 5
15 2 5 5
15 3 5 5
15 4 5 5
15 5 5 5
15 6 5 5
15 7 5 5
15 8 5 5
15 9 5 5
15 10 5 5
15 11 5 5
15 12 5 5
15 13 5 5
15 14 5 5
15 15 5 5
15 16 5 5
15 17 5 5
15 18 5 5
15 19 5 5
15 20 5 5
16 1 5 5
16 2 5 5
16 3 5 5
16 4 5 5
16 5 5 5
16 6 5 5
16 7 5 5
16 8 5 5
16 9 5 5
16 10 5 5
16 11 5 5
16 12 5 5
16 13 5 5
16 14 5 5
16 15 5 5
16 16 5 5
16 17 5 5
16 18 5 5
16 19 5 5
16 20 5 5
17 1 5 5
17 2 5 5
17 3 5 5
17 4 5 5
17 5 5 5
17 6 5 5
17 7 5 5
17 8 5 5
17 9 5 5
17 10 5 5
17 11 5 5
17 12 5 5
17 13 5 5
17 14 5 5
17 15 5 5
17 16 5 5
17 17 5 5
17 18 5 5
17 19 5 5
17 20 5 5
18 1 5 5
18 2 5 5
18 3 5 5
18 4 5 5
18 5 5 5
18 6 5 5
18 7 5 5
18 8 5 5
18 9 5 5
18 10 5 5
18 11 5 5
18 12 5 5
18 13 5 5
18 14 5 5
18 15 5 5
18 16 5 5
18 17 5 5
18 18 5 5
18 19 5 5
18 20 5 5
19 1 5 5
19 2 5 5
19 3 5 5
19 4 5 5
19 5 5 5
19 6 5 5
19 7 5 5
19 8 5 5
19 9 5 5
19 10 5 5
19 11 5 5
19 12 5 5
19 13 5 5
19 14 5 5
19 15 5 5
19 16 5 5
19 17 5 5
19 18 5 5
19 19 5 5
19 20 5 5
20 1 5 5
20 2 5 5
20 3 5 5
20 4 5 5
20 5 5 5
20 6 5 5
20 7 5 5
20 8 5 5
20 9 5 5
20 10 5 5
20 11 5 5
20 12 5 5
20 13 5 5
20 14 5 5
20 15 5 5
20 16 5 5
20 17 5 5
20 18 5 5
20 19 5 5
20 20 5 5*/
