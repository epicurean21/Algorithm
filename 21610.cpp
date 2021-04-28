#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;
#define MAX 52
int N, M, A[MAX][MAX], d, s;
int dx[] = {0, 0, -1, -1, -1, 0, 1, 1, 1}, dy[] = {0, -1, -1, 0, 1, 1, 1, 0, -1};
queue<pair<int, int>> cloud;
vector<pair<int, int>> m; // d, s
bool chk[MAX][MAX];

void make_clouds() {
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (A[i][j] >= 2 && !chk[i][j]) {
                A[i][j] -= 2;
                cloud.push({i, j});
            }
        }
    }
}

int change_dir(int x) {
    int tmpx = x;
    if (x <= 0)
        tmpx = N;
    else if (x > N)
        tmpx = 1;
    return tmpx;
}

int count_water() {
    int cnt = 0;
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            cnt += A[i][j];
    return cnt;
}

void magic() {
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (chk[i][j]) {
                int cnt = 0;
                for (int k = 2; k <= 8; k += 2) {
                    int nx = i + dx[k];
                    int ny = j + dy[k];
                    if (nx <= 0 || nx > N || ny <= 0 || ny > N) continue;
                    if (A[nx][ny] >= 1)
                        cnt++;
                }
                A[i][j] += cnt;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            cin >> A[i][j];
    for (int i = 0; i < M; i++) {
        cin >> d >> s;
        m.emplace_back(d, s);
    }
    for (int i = 1; i <= 2; i++) {
        cloud.push({N - 1, i});
        cloud.push({N, i});
    }
    for (int i = 0; i < M; i++) {
        if (cloud.empty())
            break;
        memset(chk, false, sizeof(chk));
        while (!cloud.empty()) { // 이동하고 구름 다 없애기
            int cx = cloud.front().first;
            int cy = cloud.front().second;
            cloud.pop();

            for (int j = 0; j < m[i].second % N; j++) {
                cx = change_dir(cx + dx[m[i].first]);
                cy = change_dir(cy + dy[m[i].first]);
            }
            A[cx][cy]++;
            chk[cx][cy] = true;
        }
        magic();
        make_clouds();
    }
    cout << count_water();
    return 0;
}