#include <iostream>
#include <vector>

using namespace std;
#define MAX 501
int N, dp[MAX][MAX];
vector<pair<int, int>> matrix;

// 행렬의 s부터 e까지 계산을 해서 최적의 값을 내는 함수
int calc(int s, int e) {
    if (e == s)
        return 0;
    if(dp[s][e])
        return dp[s][e];
    if (e - s == 1) // 한 칸차이
        return dp[s][e] = matrix[s].first * matrix[s].second * matrix[e].second;
    // 적절한 처리가 필요. 메모이제이션 ! 계산량을 줄이자.
    // How?
    // calc(s,e) 를 이전에 계산한 적이 있으면 새롭게 계산하지 않고 이전 계산내용을 사용하자! 메모이제이션

    // 여긴 처음으로 계산하니까 계산을 놔두자
    // 부분으로 다 나누어서 괜찮을 값을 구한다.

    for (int m = s; m <= e - 1; m++) {
        int tmp = calc(s, m) + calc(m + 1, e) + (matrix[s].first * matrix[m].second * matrix[e].second);
        if (!dp[s][e] || tmp < dp[s][e])
            dp[s][e] = tmp;
    }

    // 처음으로 계산 했기 때문에 계산 결과를 저장한다.
    return dp[s][e];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    matrix.resize(N + 1);
    for (int i = 0; i < N; i++)
        cin >> matrix[i].first >> matrix[i].second;

    cout << calc(0, N - 1) << "\n";
    return 0;
}