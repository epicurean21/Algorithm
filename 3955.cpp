/*
 * X: 인당 나누어줄 사탕 개수
 * Y: 사탕 봉지의 수
 * A * X + 1 = B * Y
 * Ax + By = C 형태로
 * -Ax + By = 1
 * A(-x) + By = 1
 *
 * D = gcd(A, B)
 * D * k = C --> C % D == 0 이어야만 해를 가질 수 있음 (배주 항등식)
 *
 * 확장 유클리드 호제법을 이용하여 s, t, r을 찾아내자
 * x0 = s * C/D
 * y0 = t * C/D
 *
 * 일반 해 공식
 * x = x0 + B/D * k
 * y = y0 - A/D * k
*/
/*
 * Cy=Kx+1
 * Cy = 1 mod K
 * 인 C와 K를 구한다.
 */
#include <iostream>

using namespace std;
#define INF 1e9
int T, K, C;

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int eGcd(int a, int b) {
    int s0 = 1, t0 = 0, r0 = a;
    int s1 = 0, t1 = 1, r1 = b;
    int tmpA = a;
    int tmp;
    while(r1 != 0) {
        int q = r0 / r1;
        tmp = r0 - q * r1;
        r0 = r1;
        r1 = tmp;

        tmp = s0 - q * s1;
        s0 = s1;
        s1 = tmp;

        tmp  = t0 - q * t1;
        t0 = t1;
        t1 = tmp;
    }
    while(t0 < 0)
        t0 += tmpA;
    return t0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> T;
    while (T--) {
        cin >> K >> C;
        if(C == 1) {
            if(K + 1 > INF)
                cout << "IMPOSSIBLE\n";
            else
                cout << K + 1 << "\n";
        }
        else if(K == 1)
            cout << "1\n";
        else if(gcd(K, C) != 1)
            cout << "IMPOSSIBLE\n";
        else {
            int tmp = eGcd(K, C);
            if(tmp > INF)
                cout << "IMPOSSIBLE\n";
            else
                cout << tmp << "\n";
        }

    }
    return 0;
}