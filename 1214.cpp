/**
 * 1214 쿨한 물건 구매
 * 수학, 브루트포스, 정수론
 * D원보다 크거나 같은 금액을 P, Q의 조합으로 만들어야한다
 * D = 21, P = 7, Q = 13 이라면
 * 지불최소 금액은 21 (P*3)이다
 * 7, 13, 14, 20, 21, 26, 27, 28 이런식으로 조합을 만들어야한다.
 */
#include <iostream>

using namespace std;

int D, P, Q;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> D >> P >> Q;
    if (P > Q)
        swap(P, Q);

    if (D % P == 0 || D % Q == 0) // 나눠 떨어짐
        cout << D << "\n";
    else {

    }

    return 0;
}