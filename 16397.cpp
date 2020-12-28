#include <iostream>
#include <queue>
#include <cmath>

using namespace std;
#define MAX 100001

int map[MAX];
queue<pair<int, int>> bfs;
int N, T, G;

void BFS(int cur, int t) {
    map[cur] = 1;
    bfs.push({cur, 0});
    while (!bfs.empty()) {
        int c = bfs.front().first;
        int time = bfs.front().second;
        if (time >= t || c == G)
            break;
        bfs.pop();
        int nc1 = c + 1;
        if(!map[nc1]) {
            map[nc1] = time + 1;
            bfs.push({nc1, time + 1});
        }

        int nc2 = c * 2;
        if(nc2 > 99999) continue;
        int tmp = nc2;
        int sz = 0;
        while (tmp /= 10)
            sz++;
        nc2 -= (int) pow(10, sz);

        if (nc2 < 0)
            nc2 = 0;
        if (!map[nc2]) {
            map[nc2] = time + 1;
            bfs.push({nc2, time + 1});
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> T >> G;
    BFS(N, T);
    map[N] = 0;
    if (N == G || map[G])
        cout << map[G] << "\n";
    else
        cout << "ANG\n";
    return 0;
}