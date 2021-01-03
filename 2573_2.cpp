#include<iostream>
#include<cstring>
#include<queue>

#define endl "\n"
#define MAX 300
using namespace std;

int N, M;
int MAP[MAX][MAX];
int C_MAP[MAX][MAX];
bool Visit[MAX][MAX];

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

void BFS(int a, int b) {
    queue<pair<int, int>> Q;
    Q.push(make_pair(a, b));
    Visit[a][b] = true;

    while (Q.empty() == 0) {
        int x = Q.front().first;
        int y = Q.front().second;
        Q.pop();

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && ny >= 0 && nx < N && ny < M) {
                if (Visit[nx][ny] == false && MAP[nx][ny] != 0) {
                    Visit[nx][ny] = true;
                    Q.push(make_pair(nx, ny));
                }
            }
        }
    }
}

int Melt(int x, int y) {
    int Cnt = 0;
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (MAP[nx][ny] == 0) Cnt++;
    }
    return Cnt;
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> M;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            cin >> MAP[i][j];

    int Year = 0;
    while (1) {
        int Land_Cnt = 0;
        memset(Visit, false, sizeof(Visit));
        memset(C_MAP, 0, sizeof(C_MAP));

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (MAP[i][j] != 0 && Visit[i][j] == false) {
                    Land_Cnt++;
                    BFS(i, j);
                }
            }
        }

        if (Land_Cnt >= 2) {
            cout << Year << "\n";
            break;
        }
        if (Land_Cnt == 0) {
            cout << "0\n";
            break;
        }

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (MAP[i][j] != 0) {
                    C_MAP[i][j] = MAP[i][j] - Melt(i, j);
                    if (C_MAP[i][j] < 0) C_MAP[i][j] = 0;
                }
            }
        }

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                MAP[i][j] = C_MAP[i][j];
            }
        }
        Year++;
    }
    return 0;
}