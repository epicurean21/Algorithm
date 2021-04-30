#include <iostream>

using namespace std;
#define MAX 101
int N, M, a, b, ranking[MAX];
bool possible[MAX][MAX];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    for (int i = 0; i < M; i++) {
        cin >> a >> b;
        possible[a][b] = true;
    }
    for (int k = 1; k <= N; k++)
        for (int i = 1; i <= N; i++)
            for (int j = 1; j <= N; j++)
                if (possible[i][k] && possible[k][j])
                    possible[i][j] = true; // i > j를 알게된다

    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if(i == j) continue;
            if(!possible[i][j] && !possible[j][i]) // i > j 인걸 모르면서 j > i 인걸 모른다
                ranking[i]++;
        }
        cout << ranking[i] << "\n";
    }
    return 0;
}