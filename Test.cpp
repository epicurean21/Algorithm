/**
 * Leetcode #7 Reverse Integer

 */
#include "../bits/stdc++.h"

using namespace std;

class Solution {
public:
    int reverse(int x) {
        int ans = 0;
        int calculateXSize = x;
        int size = 0;
        while (calculateXSize / 10) {
            size++;
            calculateXSize /= 10;
        }

        while (x / 10) {
            if (x % 10 != 0) {
                int tmp = pow(10, size--) * (x % 10);
                ans += tmp;
            }
            x /= 10;
        }
        if (x < 0)
            ans *= -1;

        return ans;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    Solution s = *new Solution();
    int x = 120;
    cout << s.reverse(x) << '\n';
    return 0;
}