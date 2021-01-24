#include <iostream>

using namespace std;

#define MAX 17
#define INF 987654321
int N, W[MAX][MAX], dp[1 << MAX][MAX]; // dp[선택한 도시들][마지막 여행한 도시]
// W[i][j] : i -> j 까지 이동 거리
// dp[i][j] : [i][j] 도시를 i 처럼 거쳐왔고, 현재 j에 있을때 이동한 거리
// 시작점으로 다시 와야함
// 0번도시 1번도시 2번도시 ...
/*
 * 비트마스킹
 * int x;
 * x |= (1 << 10); 마스킹
 * x & (1 << 10); 체킹
 * 탑다운, 함수(끝, 이용한도시): 함수(1, 1): 1번도시를 방문 했을 때 TSP의 값은 얼마니 ?
 * 바텁업으로 시도해보자!
 */

// pos 번째의 bit를 set: 가장 낮은자리수가 0
int bitSet(int originalBit, int pos) {
    return originalBit | (1 << pos);
}

int bitUnset(int originalBit, int pos) {
    return originalBit & (~(1 << pos));
}

int bitCheck(int originalBit, int pos) {
    if (((originalBit & (1 << pos)) == 0)) return false;
    else
        return true;
}

int min(int a, int b) {
    return a > b ? b : a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> W[i][j];

    // dp 배열 초기화
    for (int i = 0; i < (1 << MAX); i++)
        for (int j = 0; j < MAX; j++)
            dp[i][j] = INF;


    // 시작점 세팅: 0번째 도시에서 시작
    dp[1][0] = 0; // [0번째 도실ㄹ 거쳐왔고][현재 0번째 도시이니까]
    for (int i = 0; i < (1 << N); i++) {
        // 전개 dp[i][j]
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                // k 로 갈 수 있는지
                if (bitCheck(i, k)) continue; // 이미 가본곳이면 못가니까
                if (W[j][k] == 0) continue; // 갈수없는길
                int next = bitSet(i, k);
                dp[next][k] = min(dp[next][k], dp[i][j] + W[j][k]);
            }
        }
    }

    // 모든 도시를 순회했고, 시작점으로 가는 처리를 하면서 답을 구함
    // 비용을 구하면서 정답을 구한다.
    int ans = INF;
    int lastState = (1 << N) - 1; // 모든 도시를 방문한 상태
    for (int i = 0; i < N; i++) {
        if (W[i][0] == 0) continue; // 길이 없을경우
        int tmp = dp[lastState][i] + W[i][0]; // 다 가본 상태 + 시작점으로 가는 경로
        ans = min(tmp, ans);
    }
    cout << ans << '\n';
    return 0;
}