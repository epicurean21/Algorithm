#include <iostream>
#include <map>
#include <queue>

using namespace std;

int T, dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1}, ans;
char board[4][4];
bool chk[4][4];
map<string, int> m;

void init() {
    m.clear();
    ans = 1;
}

void bfs(int x, int y) {
    queue<pair<pair<int, int>, pair<string, int>>> q;
    string startStr = "";
    q.push({{x,                      y},
            {startStr + board[y][x], 1}});
    while (!q.empty()) {
        int curx = q.front().first.first;
        int cury = q.front().first.second;
        string str = q.front().second.first;
        int cnt = q.front().second.second;
        q.pop();
        if (cnt == 7) {
            if (m.count(str) == 0) {
                m.insert({str, ans++});
            }
            continue;
        }
        for (int i = 0; i < 4; i++) {
            int nx = curx + dx[i];
            int ny = cury + dy[i];

            if (nx < 0 || nx >= 4 || ny < 0 || ny >= 4) continue;
            string tmp = str + board[ny][nx];
            q.push({{nx,  ny},
                    {tmp, cnt + 1}});
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> T;
    for (int t = 1; t <= T; t++) {
        init();
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                cin >> board[i][j];

        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                bfs(j, i);
        cout << "#" << t << " " << m.size() << '\n';
    }
    return 0;
}

/*
4
1 1 1 1
1 1 1 2
1 1 2 1
1 1 1 1

2 1 1 1
1 1 1 2
2 1 2 1
1 1 1 1

1 3 1 1
0 1 1 2
1 2 2 1
1 1 1 7

0 1 1 1
0 1 1 2
1 1 2 1
2 3 1 9
 */