#include <iostream>

using namespace std;
#define MAX 11

int N, ans = 9999999;
int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};
int map[MAX][MAX];
bool been[MAX][MAX];

int min(int a, int b) {
    return a > b ? b : a;
}

void unplant(int x, int y) {
    been[y][x] = false;
    for (int i = 0; i < 4; i++)
        been[y + dy[i]][x + dx[i]] = false;
}

void plant(int x, int y) {
    been[y][x] = true;
    for (int i = 0; i < 4; i++)
        been[y + dy[i]][x + dx[i]] = true;
}

int check(int x, int y) { // 씨앗 심을 수 있는지 확인
    int cnt = 0;
    if(been[y][x])
        return -1;
    cnt += map[y][x];
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx < 0 || nx >= N || ny < 0 || ny >= N)
            return -1;
        if(been[ny][nx])
            return -1;
        cnt += map[ny][nx];
    }
    return cnt;
}

void dfs(int price, int seed) {
    if(!seed) {
        ans = min(ans, price);
        return;
    }
    for(int i = 1; i < N; i++) {
        for(int j = 1; j < N; j++) {
            int tmp = check(j, i);
            if(tmp != -1) {
                plant(j, i);
                dfs(price + tmp, seed - 1);
                unplant(j, i);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> map[i][j];

    dfs(0, 3);
    cout << ans << "\n";
    return 0;
}