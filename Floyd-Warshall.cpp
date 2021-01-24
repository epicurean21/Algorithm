#include <iostream>

using namespace std;
#define MAX 102
#define INF 987654321
// 플로이드 와샬
int n, m, a, b, c;
int dist[MAX][MAX];
int ans[MAX][MAX];

int min(int a, int b) {
    return a > b ? b : a;
}

void init() {
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == j) continue;
            dist[i][j] = INF;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    init();

    for (int i = 0; i < m; i++) {
        cin >> a >> b >> c;
        if (dist[a][b] > c)
            dist[a][b] = c;
    }
    for (int i = 1; i <= n; i++) { // 중간점
        for (int j = 1; j <= n; j++) { // 시작점
            for (int k = 1; k <= n; k++) { // 끝점
                dist[j][k] = min(dist[j][k], dist[j][i] + dist[i][k]);
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (dist[i][j] == INF)
                cout << "0 ";
            else
                cout << dist[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
}