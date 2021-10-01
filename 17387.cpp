/**
 * 17387: 선분 교차 2
 * CCW, 선분 교차 판별
 */
#include <iostream>

using namespace std;
int X[4], Y[4];

int ccw(int x1, int y1, int x2, int y2, int x3, int y3) {
    return x1 * y2 + x2 * y3 + x3 * y1 - (x2 * y1 + x3 * y2 + x1 * y3);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    for (int i = 0; i < 4; i++)
        cin >> X[i] >> Y[i];

    if (ccw(X[0], Y[0], X[1], Y[1], X[3], Y[3]) == 0)
        cout << "0\n";
    else
        cout << "1\n";

    return 0;
}