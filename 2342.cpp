#include <iostream>
#include <cstring>

using namespace std;
#define MAX 100001
#define INF 978654321
int order[MAX], a, power[5][5], dp[MAX][5][5]; // dp[DDR의 단계][왼발의 위치][오른발의 위치] 일때의 소모한 최소의 힘
void powerInit() {
    for (int i = 1; i <= 4; i++)
        power[0][i] = 2; // 발이 0 에서 1, 2, 3, 4로는 2의 힘이 든다
// 인접한 지점으로 움직일때,, 힘은 3 든다. 1 -> 2, 1 -> 4
    power[1][2] = power[1][4] = 3;
    power[2][1] = power[2][3] = 3;
    power[3][2] = power[3][4] = 3;
    power[4][1] = power[4][3] = 3;
// 반대편으로 움직일때 힘은 4 든다.
    power[1][3] = power[3][1] = 4;
    power[2][4] = power[4][2] = 4;

    // 같은 곳 다시 밟기 힘은 1 든다
    for (int i = 1; i <= 4; i++)
        power[i][i] = 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    while (1) {
        cin >> order[a + 1];
        if (order[a + 1] == 0)
            break;
        a++;
    }
    memset(dp, INF, sizeof(dp));
    powerInit();
    // 단계를 진행
    dp[0][0][0] = 0;
    for (int i = 0; i < a; i++) {
        /*
         * 할일은 <i> 단계의 결과는 잘 끝냈고, <i + 1> 단계로 가고싶음.
         * 내가 밟아야 할 DDR의 번호는 i + 1을 예정임
         */
        for (int l = 0; l <= 4; l++) {
            for (int r = 0; r <= 4; r++) {
                int ddr = order[i + 1], used_power;
                // ddr은 다음 위치 값
                // dp[i][l][r] : i단계일때 왼발 l, 오른발 r 일때 소모한 힘
                // 처리할 것들. 같은 위치는 안된다 !
                // ddr == r, l == ddr 이런거 안됨

                // 오른발을 움직여봄 ==> dp[i+1][l][ddr]
                used_power = dp[i][l][r] + power[r][ddr];
                if (ddr != l && dp[i + 1][l][ddr] > used_power)
                    dp[i + 1][l][ddr] = used_power;

                // 왼발을 움직여봄 ==> dp[i + 1][ddr][r]
                used_power = dp[i][l][r] + power[l][ddr];
                // 경우의 수는 많은데 그 중 최소의 값으로 갖고싶다.
                if (ddr != r && used_power < dp[i + 1][ddr][r])
                    dp[i + 1][ddr][r] = used_power;
            }
        }
    }

    // 무엇을 출력할 것인가 ? ... a 단계까지 왔을때 많으 발의 상태가 있을텐데 그중 가장 작은 값
    int ans = INF;
    for (int l = 0; l <= 4; l++) {
        for (int r = 0; r <= 4; r++) {
            if (dp[a][l][r] < ans)
                ans = dp[a][l][r];
        }
    }
    cout << ans << '\n';
    return 0;
}