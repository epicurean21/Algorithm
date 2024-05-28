/**
 * Leetcode #7 Reverse Integer
 * Math
 */
#include "../bits/stdc++.h"

using namespace std;

class Solution {
public:
    int reverse(int x) {
        int ans = 0;
        while (x) {
            if (ans > INT_MAX / 10 || ans < INT_MIN / 10)
                return 0;
            ans = ans * 10 + x % 10;
            x /= 10;
        }
        return ans;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    Solution s = *new Solution();
    int x = -123;
    cout << s.reverse(x) << '\n';
    return 0;
}