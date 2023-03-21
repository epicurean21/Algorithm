/**
 * 10986 나머지 합
 * 수학, 누적 합
 * (a + b) % c 는 (a % c) + (b % c) % c 는 같다는 성질을 이용한다.
 * 누적 합 구간에서 나누어 떨어지는 것
 * 즉, (A[j] - A[i - 1]) % M = 0 인 개수를 찾는건, (A[j] % M) - (A[i - 1]) 의 개수와 같다.
 * 근데 A[i] % M 이 0 이라면 그 자체를 더해준다.
 */
#include "iostream"

using namespace std;
#define MAX 1000001
#define ll long long

int n, m;
ll cnt, arr[MAX], arrSum[MAX], arrCal[MAX];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> arr[i];
        arrSum[i] = (arrSum[i - 1] + arr[i]) % m;
        if (arrSum[i] == 0) cnt++;
        arrCal[(int) arrSum[i]]++;
    }

    for (int i = 0; i < m; i++) {
        if (arrCal[i] > 1) cnt += (arrCal[i] * (arrCal[i] - 1l)) / 2l;
    }

    cout << cnt << '\n';
    return 0;
}