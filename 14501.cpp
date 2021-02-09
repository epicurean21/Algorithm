#include <iostream>
// DP
// 퇴사
using namespace std;
#define MAX 16
int N, money[MAX], pay, T, P; // money가 dp배열
pair<int, int> resign[MAX]; // 입력 표

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> T >> P;
        resign[i] = {T, P};
    }
    for (int i = 1; i <= N + 1; i++) {
        pay = max(pay, money[i]); // i번째 날까지의 금액 중 최댓값.
        if (i + resign[i].first > N + 1) // 만약 i번째 날은 일할수없는날이면 continue
            continue;
        // money[i + 필요한 일] 즉 해당 날 최대 소요하는 i번째 날까지의 벌 수 있는 금액은, pay + 해당날금액 또는 이미 그날.
        money[i + resign[i].first] = max(pay + resign[i].second, money[i + resign[i].first]);
        /*
         * 즉 i가 1이면 첫 째날 소요일 3일, 금액 10원
         * money[i + 3] 즉 money[4] 4일째 날까지의 최대 금액은 pay + 1일째날 10원
         *
         * i = 4 4일째 날엔 소요 1일 금액 20
         * money[i + 1] 즉 5일째까지의 최대금액은 max(money[5], pay + 4일째날 돈 20) 이때 pay는 money[i]로
         */
    }
    cout << pay << '\n';
    return 0;
}