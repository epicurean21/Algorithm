#include <iostream>

using namespace std;
#define MAX 1502
int N, map[MAX][MAX];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> map[i][j];

    return 0;
}