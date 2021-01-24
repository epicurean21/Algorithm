#include <iostream>
#include <cstring>
using namespace std;
#define MAX 1002
int T, N, card[MAX], subsum[MAX]; // subsum[i]: 1~ i 까지의 합
int k_dp[MAX][MAX], m_dp[MAX][MAX];

int m_play(int, int);

int k_play(int, int);

int max(int a, int b) {
    return a > b ? a : b;
}

int getSum(int s, int e) { // 카드 s 부터 e 까지의 합
    return subsum[e] - subsum[s - 1];
}

int k_play(int s, int e) {
    if (s == e) // 한장 남았을 때
        return card[s];

    if (k_dp[s][e] != -1)
        return k_dp[s][e];
    /*
     * 한장을 뽑고 근우의 턴에 넘겼을 때 나한테 이득인가 ? 를 고려해야한다 (내가 얻는 점수)
     * 가장 왼쪽을 가져가거나
     * 근우가 지금 가져가는 카드로 얻는 값: card[s]
     * 명우가 최선을 다해서 얻는 점수: m_play(s+1,e)
     * 근우가 너머지 플레이에서 얻는 점수 : [s + 1 ~ e] 까지의 합 - "명우가 최선을 다해서 얻는 점수"
     */

    int left = 0, right = 0;
    left = card[s] + getSum(s + 1, e) - m_play(s + 1, e);
    right = card[e] + getSum(s, e - 1) - m_play(s, e - 1);

//    card[s], m_play(s + 1, e);
//    가장 오른쪽을 가져가거나
//    card[e], m_play(s, e - 1);

    // 최종 근우는 left, right 중 큰 것을 하면 됨
    return k_dp[s][e] = max(left, right);
}

int m_play(int s, int e) {
    if (s == e)
        return card[s];

    if (m_dp[s][e] != -1)
        return m_dp[s][e];

    int left = 0, right = 0;
    left = card[s] + getSum(s + 1, e) - k_play(s + 1, e);
    right = card[e] + getSum(s, e - 1) - k_play(s, e - 1);

    return m_dp[s][e] = max(left, right);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> T;
    while (T--) {
        cin >> N;
        memset(card, 0, sizeof(card));
        memset(k_dp, -1, sizeof(k_dp));
        memset(m_dp, -1, sizeof(m_dp));
        for (int i = 1; i <= N; i++) {
            cin >> card[i];
            subsum[i] = subsum[i -1] + card[i];
        }

        cout << k_play(1, N) << "\n";
    }
    return 0;
}