/**
 * 11758: CCW
 * 기하학, CCW 알고리즘 (Counter-ClockWise Algorithm)
 * CCW: 평면에 놓여진 세 점의 방향관계를 구하는 알고리즘
 * 벡터의 외적 개념을 사용한다!
 *
 * 예를들어, 세 점이 주어진 경우, 이 세 점이 시계방향인 관계인지,
 * 시계 반대 방향인지, 혹은 평행한 관계인지를 따지는 것이 목표이다.
 *
 * CCW 알고리즘에서, 시계방향일 때 음수, 시계 반대 방향일 때 양수, 평행일 때 0을 Return 한다.
 *
 * 1. A, B, C 순서로 방향관계를 알고싶다면 A, B를 연결한 AB 벡터와, A, C를 연결한 AC 벡터를 고려한다.
 * 2. 두 벡터의 외적값을 따진다.
 * 외적의 경우는 교환법칙이 성립하지 않기에, A, B, C 순서로 방향관계를 알고싶다면, AB벡터 x AC벡터로 구해주어야한다.
 *
 * A(x1,y1), B(x2, y2), C(x3, y3) 라면 ABC의 순서 즉 반시계방향의 값을 알고싶다면
 * CCW 함수의 return 값은 x1y2 + x2y3 + x3y1 - (x2y1 + x3y2 + x1y3)가 된다.
 * 양수면 시계반대방향, 음수면 시계방향, 0이면 평행이다~
 */
#include <iostream>

using namespace std;

int X_1, X_2, X_3, Y_1, Y_2, Y_3;

int ccw(int x1, int y1, int x2, int y2, int x3, int y3) {
    return x1 * y2 + x2 * y3 + x3 * y1 - (x2 * y1 + x3 * y2 + x1 * y3);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> X_1 >> Y_1 >> X_2 >> Y_2 >> X_3 >> Y_3;
    int ans = ccw(X_1, Y_1, X_2, Y_2, X_3, Y_3);
    if (ans > 0)cout << "1\n";
    else if (ans == 0)cout << "0\n";
    else cout << "-1\n";

    return 0;
}