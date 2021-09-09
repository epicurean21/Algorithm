/**
 * 15684: 사다리 조작
 * i 번째가 i가 나오도록
 * 이건 그냥 백트레킹 ? 어짜피 최대 설계 가능이 3개니까
 * 1개 설치시 가능한지 --> 1개로 모든 점에서 점 연결 후 확인
 * 2개 설치시 가능한지 --> ~ (백트래킹)
 * 3개 설치시 가능한지 --> ~ (백트래킹)
 *

 */

#include <iostream>

using namespace std;
#define MAX 50
int N, M, H, a, b, ans = 4, map[MAX][MAX];

void print_map() {
    cout << "\n--------------print map--------------\n";
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++)
            cout << j << " ";
        cout << '\n';
    }
    cout << '\n';
}

int min(int x, int y) {
    return x > y ? y : x;
}

bool check_possible() {
    for (int i = 1; i <= N; i++) {
        int cur = i; // 시작 세로 줄

        for (int j = 1; j <= H; j++) {
            if (map[j][cur]) // 연결되있음 + 1 (오른쪽)
                cur++;
            else if (map[j][cur - 1]) // 왼쪽
                cur--;
        }

        if (cur != i)
            return false;
    }

    return true;
}

void find_min(int cur, int cnt) {
    if (cnt > 3) return;

    if (check_possible()) {
        ans = min(ans, cnt);
        return;
    }

    for (int i = cur; i <= H; i++) {
        for (int j = 1; j <= N; j++) {
            if (map[i][j] || map[i][j - 1] || map[i][j + 1])
                continue;

            map[i][j] = 1;
            find_min(i, cnt + 1);
            map[i][j] = 0;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M >> H; // N: 세로선 개수 1 ~ N, M: 가로선 개수 1 ~ M, H: 가로선 놓을 수 있는 위치 개수

    for (int i = 0; i < M; i++) {
        cin >> a >> b; // b번 & b+1번을 a번 점선 위치에서 연결 즉 a는 가로 b는 세로
        map[a][b] = 1;
    }

    find_min(1, 0);

    if (ans == 4)
        cout << "-1\n";
    else
        cout << ans << "\n";

    return 0;
}