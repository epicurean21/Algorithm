#include <iostream>

using namespace std;
#define MAX 100002
int map[MAX][3];
int dp_min[2][3], dp_max[2][3];
int N, curY, curX[3];
pair<int,int> ans;

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a > b ? b : a;
}

void init() {
    // 0층 초기화, 즉 입력값의 1층으로 만들어준다.
    dp_min[0][0] = dp_max[0][0] = map[1][0];
    dp_min[0][1] = dp_max[0][1] = map[1][1];
    dp_min[0][2] = dp_max[0][2] = map[1][2];
}

pair<int,int> DP() {
    for (int i = 2; i <= N; i++) {
        dp_max[1][0] = map[i][0] + max(dp_max[0][0], dp_max[0][1]);
        dp_max[1][1] = map[i][1] + max(dp_max[0][0], max(dp_max[0][1], dp_max[0][2]));
        dp_max[1][2] = map[i][2] + max(dp_max[0][1], dp_max[0][2]);

        dp_max[0][0] = dp_max[1][0];
        dp_max[0][1] = dp_max[1][1];
        dp_max[0][2] = dp_max[1][2];

        dp_min[1][0] = map[i][0] + min(dp_min[0][0], dp_min[0][1]);
        dp_min[1][1] = map[i][1] + min(dp_min[0][0], min(dp_min[0][1], dp_min[0][2]));
        dp_min[1][2] = map[i][2] + min(dp_min[0][1], dp_min[0][2]);

        dp_min[0][0] = dp_min[1][0];
        dp_min[0][1] = dp_min[1][1];
        dp_min[0][2] = dp_min[1][2];
    }
    pair<int,int> sol = {max(dp_max[0][0], max(dp_max[0][1], dp_max[0][2])), min(dp_min[0][0], min(dp_min[0][1],dp_min[0][2]))};
    return sol;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N;
    for (int i = 1; i <= N; i++)
        for (int j = 0; j < 3; j++)
            cin >> map[i][j];

    init();
    ans = DP();
    cout << ans.first << " " << ans.second << "\n";
    return 0;
}