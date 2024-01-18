#include "iostream"
#include "math.h"

using namespace std;
int t, x_1, y_1, r_1, x_2, y_2, r_2;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> t;
    while (t--) {
        cin >> x_1 >> y_1 >> r_1 >> x_2 >> y_2 >> r_2;

        double distance = sqrt(pow(x_1 - x_2, 2) + pow(y_1 - y_2, 2));
        int radius_sum = r_1 + r_2;
        int radius_diff = abs(r_1 - r_2);

        if (distance == radius_sum || distance == radius_diff) { // 외접 or 내접
            cout << "1\n";
        } else if (distance == 0) { // 같은 원
            if (radius_diff == 0) {
                cout << "-1\n";
            } else {
                cout << "0\n";
            }
        } else if (distance < radius_sum && distance > radius_diff) { // 두 점서 만남
            cout << "2\n";
        } else { // 그 외 안만남
            cout << "0\n";
        }
    }

    return 0;
}