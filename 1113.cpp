#include<iostream>
#include<queue>
#include<string>

using namespace std;

const int MAX = 52;
int map[MAX][MAX], n, m, maximum = 0, ans = 0;
int dy[4] = {-1, 1, 0, 0}, dx[4] = {0, 0, -1, 1};

struct coor {
    int y;
    int x;
};
queue<coor> q;

void bfs(int h) {
    map[0][0] = h;
    q.push({0, 0});
    while (!q.empty()) {
        int y = q.front().y;
        int x = q.front().x;
        q.pop();

        int ny, nx;
        for (int i = 0; i < 4; i++) {
            ny = y + dy[i];
            nx = x + dx[i];
            if (ny < 0 || ny > n + 1 || nx < 0 || nx > m + 1) continue;
            if (map[ny][nx] < h) {
                map[ny][nx] = h;
                q.push({ny, nx});
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        string tmp;
        cin >> tmp;
        for (int j = 1; j <= m; j++) {
            map[i][j] = tmp[j - 1] - '0';
            if (map[i][j] > maximum) maximum = map[i][j];
        }
    }

    /*
        0000000
        0166610
        0611160
        0166610
        0000000
        이런식으로 입력을 받는다. 그다음 1부터 가장 높은 Max (maximum) 까지 돌면서 bfs를 실행
        
        bfs에서 인자로 받은 h값 (높이) 보다 작은 값이 map[][]에 존재한다면 해당 값을 i로 변경한다.
        
        bfs를 돌고 나온 다음, map에 h 보다 작은 값이 있다면 + 씩 높히면서 정답값도 1씩 증가시켜준다.
     */
    for (int h = 1; h <= maximum; h++) {
        bfs(h);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (map[i][j] < h) {
                    ans += 1;
                    map[i][j] += 1;
                }
            }
        }
    }
    cout << ans << '\n';
    return 0;
}
/*
4 4
5334
3023
4014
5544
 */