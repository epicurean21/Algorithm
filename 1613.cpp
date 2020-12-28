#include <iostream>

using namespace std;
#define MAX 401
#define INF 999999

int N, K, S, A, B;
int map[MAX][MAX];

int min(int a, int b) {
    return a > b ? b : a;
}

void reset() {
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            if (i == j)
                map[i][j] = 0;
            else
                map[i][j] = INF;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    reset();
    cin >> N >> K;
    for (int i = 0; i < K; i++) {
        cin >> A >> B;
        map[A][B] = 1;
    }
    for (int k = 1; k <= N; k++)
        for (int i = 1; i <= N; i++)
            for (int j = 1; j <= N; j++)
                map[i][j] = min(map[i][j], map[i][k] + map[k][j]);


    cin >> S;
    for (int i = 0; i < S; i++) {
        cin >> A >> B;
        if(map[A][B] == INF && map[B][A] == INF)
            cout << "0\n";
        else if(map[A][B] != INF)
            cout << "-1\n";
        else if(map[B][A] != INF)
            cout << "1\n";

    }

    return 0;
}