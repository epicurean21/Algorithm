/**
 * 1326 폴짝 폴짝
 * BFS, 그래프 탐색
 * ㅂㅅ같은 문제;;
 */
#include <iostream>
#include <vector>
#include <queue>

using namespace std;
#define MAX 10002
int N, a, b, steppingStone[MAX];
bool visited[MAX];

void bfs(int start) {
    queue<pair<int, int>> q;
    q.push({start, 0});
    visited[start] = true;
    while (!q.empty()) {
        int cur = q.front().first;
        int cnt = q.front().second;
        q.pop();
        if (cur == b) {
            cout << cnt << "\n";
            exit(0);
        }
        int moveSize = steppingStone[cur];
        for (int i = 1; cur + (moveSize * i) <= N; i++) {
            int nxt = cur + (moveSize * i);
            if (!visited[nxt]) {
                visited[nxt] = true;
                q.push({nxt, cnt + 1});
            }
        }
        for (int i = 1; cur - (moveSize * i) >= 1; i++) {
            int nxt = cur - (moveSize * i);
            if (!visited[nxt]) {
                visited[nxt] = true;
                q.push({nxt, cnt + 1});
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> steppingStone[i];
    }
    cin >> a >> b;
    bfs(a);
    return 0;
}