/**
 * 1002: 터렛
 * 수학, 기하학
 * r1과 r2가 있을 때 류재명이 있을 수 있는 좌표 수
 */
#include <iostream>

using namespace std;

int T;
int x1, y1, r1, x2, y2, r2;

int main() {
    int d, radius_diff, radius_sum;
    cin >> T;

    while (T--) {
        cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;
        d = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
        radius_diff = (r1 - r2) * (r1 - r2);
        radius_sum = (r1 + r2) * (r1 + r2);

        if (d == 0) {
            if (radius_diff == 0) cout << "-1\n";
            else cout << "0\n";
        } else if (d == radius_diff || d == radius_sum) cout << "1\n";
        else if (radius_diff < d && d < radius_sum) cout << "2\n";
        else cout << "0\n";
    }
}