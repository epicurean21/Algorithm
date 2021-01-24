#include <iostream>
#include <vector>

using namespace std;
#define MAX 2002
#define ll long long
int N, cake[MAX];
ll ans, dp[MAX][MAX]; // dp[i][j]: JOI군이 바라볼 때 왼쪽에는 [i]번째, 오른쪽에는 [j]번째 케이크일때 가장 많이 먹을 수 있는 케익의 양
ll J_eat(int, int), I_eat(int, int);

int max(int a, int b) {
    return a > b ? a : b;
}
// Joi 군이 먹을 차례가 되었는데 바라볼 때 왼쪽은 l 케이크, 오른쪽은 r 케이크가 있을때 많이 먹는 값.
ll J_eat(int l, int r) {
    if (l == r)
        return cake[l];
    if (dp[l][r])
        return dp[l][r];

    //먹을 수 있는 경우의 수
    // l을 먹거나 r 을 먹거나. cake[l] or cake[r]
    // 원형히니가 mod 연산을 해도댐
    int nextl, nextr;
    nextl = l + 1;
    if (nextl == N) nextl = 0;
    nextr = r - 1;
    if (nextr < 0) nextr = N - 1;
/*
 *  l을 먹으면
    cake[l] + I_eat(nextl, r);
    r을 먹으면
    cake[r] + I_eat(l, nextr);
    이 둘중 큰거를 먹는다.
 */
    return dp[l][r] = max(cake[l] + I_eat(nextl, r), cake[r] + I_eat(l, nextr));
}

// I양이 먹을 차례가 되었는데 I양이 많이 먹을 수 있는 값
// I양이 먹을 차례가 되었는데 J군이 많이 먹을 수 있는 값.
ll I_eat(int l, int r) {
    if (l == r)
        return 0; // I 양이 먹으면 Joi 가 먹을 수 있는건 0이다.
    // I양은 l, r 중 큰쪽을 가져가야한다.
    if (cake[l] > cake[r]) {
        // cake[l] 먹자
        int nextl = l + 1;
        if (nextl == N) nextl = 0;
        return J_eat(nextl, r);
    } else {
        // cake[r] 먹자
        int nextr = r - 1;
        if (nextr < 0) nextr = N - 1;
        return J_eat(l, nextr);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    for (int i = 0; i < N; i++)
        cin >> cake[i];

    if (N == 1) {
        cout << cake[0] << '\n';
        return 0;
    }
    for (int i = 0; i < N; i++) {
        // i 번째 케이크를 J 군이 먹으면서 시작.
        int nextl = i + 1;
        int nextr = i - 1;
        if (nextl == N) nextl = 0;
        if (nextr < 0) nextr = N - 1;
        ans = max(ans, cake[i] + I_eat(nextl, nextr));
    }
    cout << ans << '\n';
    return 0;
}