/**
 * 3085 사탕 게임
 * 구현, 브루트포스
 */
#include "iostream"

using namespace std;
#define MAX 51
int N, ans, dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};
char candy_box[MAX][MAX];

int max(int x, int y) {
    return x >= y ? x : y;
}

bool is_out(int x, int y) {
    return x < 0 || y < 0 || x >= N || y >= N;
}

void eat_candy() {
    for (int i = 0; i < N; i++) {
        int cnt = 1;
        for (int j = 0; j < N - 1; j++) {
            if (candy_box[i][j] == candy_box[i][j + 1]) cnt++;
            else {
                ans = max(ans, cnt);
                cnt = 1;
            }
        }
        ans = max(ans, cnt);
    }

    for (int i = 0; i < N; i++) {
        int cnt = 1;
        for (int j = 0; j < N - 1; j++) {
            if (candy_box[j][i] == candy_box[j + 1][i]) cnt++;
            else {
                ans = max(ans, cnt);
                cnt = 1;
            }
        }
        ans = max(ans, cnt);
    }
}

void solve() {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < 4; k++) {
                int nx = j + dx[k];
                int ny = i + dy[k];
                if (is_out(nx, ny)) continue;
                char tmp = candy_box[i][j];
                candy_box[i][j] = candy_box[ny][nx];
                candy_box[ny][nx] = tmp;
                eat_candy();
                candy_box[ny][nx] = candy_box[i][j];
                candy_box[i][j] = tmp;
            }
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> N;
    for (int i = 0; i < N; i++) for (int j = 0; j < N; j++) cin >> candy_box[i][j];

    solve();
    cout << ans << "\n";

    return 0;
}