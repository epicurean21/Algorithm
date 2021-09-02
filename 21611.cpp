#include <iostream>
#include <vector>
#include <queue>

using namespace std;
#define MAX 51
int N, M, map[MAX][MAX], d, s, marbles[MAX * MAX + 1], marble_count, max_count, ans;
int dx[] = {-1, 0, 1, 0}, dy[] = {0, 1, 0, -1};
vector<vector<int>> dir_index(5); // 4개 방향,


void print() {
    cout << '\n';
    for (int i = 1; i <= marble_count; i++)
        cout << marbles[i] << " ";
    cout << "\ncur ans: " << ans << "\n";

}

void find_index(int n) {
    int sx = (n + 1) / 2;
    int sy = sx;
    pair<int, int> cur = {(n + 1) / 2, (n + 1) / 2};
    int dir = 0;
    int idx = 1;
    for (int i = 1; i <= n; i++) {
        for (int k = 0; k < 2; k++) {
            for (int j = 1; j <= i; j++) {
                int nx = cur.first + dx[dir];
                int ny = cur.second + dy[dir];
                marbles[idx++] = map[ny][nx];
                if (map[ny][nx] != 0)
                    marble_count++;
                // 방향 인덱스 저장
                if (ny == sy || nx == sx) {
                    if (ny == sy && nx > sx)  // 오른쪽임
                        dir_index[4].emplace_back(idx - 1);
                    else if (ny == sy && nx < sx) // 왼쪽
                        dir_index[3].emplace_back(idx - 1);
                    else if (ny > sy && nx == sx)
                        dir_index[2].emplace_back(idx - 1);
                    else if (ny < sy && nx == sx)
                        dir_index[1].emplace_back(idx - 1);
                }
                cur = {nx, ny};
            }
            dir = (dir + 1) % 4;
        }
    }
}

void spell(int di, int si) {
    for (int i = 0; i < si; i++) {
        int index = dir_index[di][i];
        marbles[index] = -1; // 터트려버림~
    }
}

void move_marbles() {
    queue<int> q;
    for (int i = 1; i <= marble_count; i++) {
        if (marbles[i] != -1 && marbles[i] != 0) {
            q.push(marbles[i]);
            marbles[i] = 0;
        }
    }
    marble_count = q.size();
    int i = 1;
    while (!q.empty()) {
        marbles[i++] = q.front();
        q.pop();
    }
}

void explode_marbles() { // 연속된것들 터트리기

    bool flag = true; // 움직일게 남아있으면
    while (marble_count) {
        int now = marbles[1];
        int cnt = 0;
        if (!flag)
            break;
        flag = false;

        for (int i = 1; i <= marble_count + 1; i++) {
            int next = marbles[i];
            if (now != next) {
                if (cnt >= 4) {
                    ans += cnt * now; // 폭발
                    for (int j = 1; j <= cnt; j++) {
                        marbles[i - j] = -1;
                    }
                    flag = true;
                }
                now = next;
                cnt = 1;
            } else {
                cnt++;
            }
        }
        move_marbles();
    }
}

void regrouping() {
    queue<int> q;
    int now = marbles[1];
    int next = 0;
    int cnt = 0;

    for (int i = 1; i <= marble_count; i++) {
        next = marbles[i];
        if (now != next) {
            q.push(cnt);
            q.push(now);
            now = next;
            cnt = 1;
        } else
            cnt++;
    }
    q.push(cnt);
    q.push(now);
    marble_count = q.size();
    int i = 1;
    while (!q.empty()) {
        marbles[i++] = q.front();
        q.pop();
    }
    if (marble_count > max_count) {
        for (int i = max_count + 1; i <= marble_count; i++)
            marbles[i] = 0;
        marble_count = max_count;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    max_count = N * N - 1;
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            cin >> map[i][j];

    find_index(N);
    while (M--) {
        cin >> d >> s;
        spell(d, s);
        move_marbles();
        explode_marbles();
        regrouping();
    }

    cout << ans << '\n';
    return 0;
}