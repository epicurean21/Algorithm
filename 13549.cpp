#include <iostream>
#include <queue>

using namespace std;
#define MAX 100001

int N, K, map[MAX];
bool chk[MAX];

void bfs(int start) {
    queue<int> q;
    q.push(start);
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        chk[cur] = true;

        if (cur == K) break;

        int nx = cur * 2;
        if (nx < MAX && !chk[nx]) {
            chk[nx] = true;
            map[nx] = map[cur];
            q.push(nx);
        }

        nx = cur - 1;
        if (nx >= 0 && !chk[nx]) {
            chk[nx] = true;
            map[nx] = map[cur] + 1;
            q.push(nx);
        }

        nx = cur + 1;
        if (nx < MAX && !chk[nx]) {
            chk[nx] = true;
            map[nx] = map[cur] + 1;
            q.push(nx);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> K;
    bfs(N);
    cout << map[K] << "\n";
    return 0;
}