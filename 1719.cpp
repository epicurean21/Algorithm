#include <iostream>

using namespace std;
#define MAX 201
#define INF 9999999
int N, M, A, B, C;
int map[MAX][MAX];
int dist[MAX][MAX];

void reset() {
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= N; j++) {
            if (i == j) continue;
            map[i][j] = INF;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> M;
    reset();
    for (int i = 0; i < M; i++) {
        cin >> A >> B >> C;
        map[A][B] = C;
        map[B][A] = C;
        dist[A][B] = B;
        dist[B][A] = A;
    }

    for (int k = 1; k <= N; k++) {
        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= N; j++) {
                if (map[i][j] > map[i][k] + map[k][j]) {
                    map[i][j] = map[i][k] + map[k][j];
                    dist[i][j] = dist[i][k];
                }
            }
        }
    }
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (i == j)
                cout << "- ";
            else
                cout << dist[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
}