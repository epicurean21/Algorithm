/*#include <iostream>
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
}*/
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
int curDist[MAX][MAX];
bool been[MAX][MAX];

int min(int a, int b) {
    return a > b ? b : a;
}

void reset() {
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            been[i][j] = false;
            curDist[i][j] = -1;
        }
    }
    while (!bfs.empty()) {
        bfs.pop();
    }
}


void BFS() {
    reset();
    bfs.push({{taxiX, taxiY}, 0});

    while (!bfs.empty()) {
        int cx = bfs.front().first.first;
        int cy = bfs.front().first.second;
        int dist = bfs.front().second;
        bfs.pop();
        been[cy][cx] = true;
        curDist[cy][cx] = dist;
        for (int i = 0; i < 4; i++) {
            int nx = cx + dx[i];
            int ny = cy + dy[i];
            int nextDist = dist + 1;
            if (nx <= 0 || nx > N || ny <= 0 || ny > N) continue;
            if (map[ny][nx] == 1) continue;
            if (been[ny][nx]) continue;
            been[ny][nx] = true;
            bfs.push({{nx, ny}, nextDist});
        }
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
    BFS();
    for (int i = 2; i < M + 2; i++) {
        if (!finished[i]) { // 아직 도착 안한 손님이라면
            int cx = customers[i].first.first; // 손님 x좌표
            int cy = customers[i].first.second; // y 좌표
            int dist = curDist[cy][cx]; // 택시 위치에서 손님까지 거리 계산
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