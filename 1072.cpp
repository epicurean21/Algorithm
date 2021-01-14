#include <iostream>

using namespace std;
#define MAX 1000000000
long long X, Y;
int Z;
int ans = -1;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    cin >> X >> Y;
    Z = (100 * Y) / X;

    if(Z >= 99) {
        cout << "-1\n";
    } else {
        // upper bound
        int low = 0;
        int high = MAX;
        while (low <= high) {
            int mid = (low + high) / 2;
            int tmp = (100 * (Y + mid) / (X + mid)); // 새로 구한 승률 이게 Z보다 처음으로 커지는걸 원한다.

            if (tmp <= Z) {
                low = mid + 1;
                ans = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        cout << ans << "\n";
    }
    return 0;
}