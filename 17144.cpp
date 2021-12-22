/**
 * 17144 미세먼지 안녕!
 * 구현, 시뮬레이션
 */
#include<iostream>

#define MAX 51
using namespace std;

int R, C, T;
int MAP[MAX][MAX];
int C_MAP[MAX][MAX];

int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
pair<int, int> Air_Cleaner[2];

void map_copy(int A[][MAX], int B[][MAX]) {
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            A[i][j] = B[i][j];
}

int count_map() {
    int cnt = 0;
    for (int i = 0; i < R; i++)
        for (int j = 0; j < C; j++)
            if (MAP[i][j] > 0)
                cnt += MAP[i][j];

            return cnt;
}


void spread() {
    map_copy(C_MAP, MAP);
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (MAP[i][j] != 0 && MAP[i][j] != -1) {
                int Cnt = 0;
                int Value = MAP[i][j] / 5;
                for (int k = 0; k < 4; k++) {
                    int nx = i + dx[k];
                    int ny = j + dy[k];

                    if (nx >= 0 && ny >= 0 && nx < R && ny < C) {
                        if (MAP[nx][ny] != -1) {
                            C_MAP[nx][ny] = C_MAP[nx][ny] + Value;
                            Cnt++;
                        }
                    }
                }
                C_MAP[i][j] = C_MAP[i][j] - (Cnt * Value);
            }
        }
    }
    map_copy(MAP, C_MAP);
}

void active_air_cleaner() {
    for (int Idx = 0; Idx < 2; Idx++) {
        if (Idx == 0) {
            for (int i = Air_Cleaner[Idx].first - 1; i > 0; i--)
                MAP[i][0] = MAP[i - 1][0];
            for (int i = 0; i < C - 1; i++)
                MAP[0][i] = MAP[0][i + 1];
            for (int i = 1; i <= Air_Cleaner[Idx].first; i++)
                MAP[i - 1][C - 1] = MAP[i][C - 1];
            for (int i = C - 1; i > 1; i--)
                MAP[Air_Cleaner[Idx].first][i] = MAP[Air_Cleaner[Idx].first][i - 1];
            MAP[Air_Cleaner[Idx].first][1] = 0;
        } else {
            for (int i = Air_Cleaner[Idx].first + 1; i < R - 1; i++)
                MAP[i][0] = MAP[i + 1][0];
            for (int i = 0; i < C - 1; i++)
                MAP[R - 1][i] = MAP[R - 1][i + 1];
            for (int i = R - 1; i >= Air_Cleaner[Idx].first; i--)
                MAP[i][C - 1] = MAP[i - 1][C - 1];
            for (int i = C - 1; i > 1; i--)
                MAP[Air_Cleaner[Idx].first][i] = MAP[Air_Cleaner[Idx].first][i - 1];
            MAP[Air_Cleaner[Idx].first][1] = 0;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> R >> C >> T;
    int Idx = 0;
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            cin >> MAP[i][j];
            if (MAP[i][j] == -1) {
                Air_Cleaner[Idx].first = i;
                Air_Cleaner[Idx].second = j;
                Idx++;
            }
        }
    }

    while (T--) {
        spread();
        active_air_cleaner();
    }
    cout << count_map() << "\n";
    return 0;
}
