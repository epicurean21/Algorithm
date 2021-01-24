#include <iostream>
#include <string>

using namespace std;
#define MAX 17
#define INF 10001
int N, P, cost[MAX][MAX], state;
int dp[(1 << MAX)]; //상태를 만들기 위한 최소비용
bool onOff[MAX];
string str;

int bitCount(int a) {
    int count = 0;
    while (a != 0) {
        if (a & 1) count++;
        a /= 2;
    }
    return count;
}

int bitSet(int b, int pos) {
    return b | (1 << pos);
}

int bitCheck(int b, int pos) {
    return (b & (1 << pos));
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
            cin >> cost[i][j];
    cin >> str >> P;
    for (int i = 0; i < str.length(); i++)
        if (str[i] == 'Y')
            onOff[i] = true;

    for (int i = 0; i < (1 << 16); i++)
        dp[i] = INF;

    if (P == 0) {
        cout << "0\n";
        return 0;
    }

    // 최초 시작은 어떻게 진행해야할까?
    // 힌트는 최초에 켜져있는 발전소를 아니까 상태를 만들어서, 그 상태의 dp[] = 0으로 ...
    //시작
    for (int i = 0; i < N; i++)
        if (onOff[i])
            state = bitSet(state, i);
    dp[state] = 0;

    for (int tmpState = 0; tmpState < (1 << N); tmpState++) {
        for (int i = 0; i < N; i++) {
            // state인 상태에서 i 발전소를 켤 수 있을까?
            // 켜게되면 비용은 어떻게 될까?
            // 그때 state는 어떤 모양일까?: nextState
            // nextState에는 어떤 값이 있었을까?
            int nextState, nextCost;
            if (bitCheck(tmpState, i)) continue; // 이미 켜져있는것
            nextState = bitSet(tmpState, i);
            for (int j = 0; j < N; j++) { // j 번째 발전소를 이용해서 i를 켜자 !
                if (bitCheck(tmpState, j)) { // 가 본곳만
                    nextCost = dp[tmpState] + cost[j][i];
                    if (nextCost < dp[nextState])
                        dp[nextState] = nextCost;
                }
            }
        }
    }
    // 출력
    // 답을 출력할때는 P를 고려해서 P보다 큰가를 본다
    int ans = INF;
    for (int i = 0; i < (1 << N); i++) {
        if (bitCount(i) >= P) {
            // 작업
            ans = min(ans, dp[i]);
        }
    }
    if(ans == INF)
        cout << "-1\n";
    else
        cout << ans << '\n';
    return 0;
}