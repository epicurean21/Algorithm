/**
 * Leetcode #11 Container with most water
 * solved with two pointer
 * be sure to adjust value left and right, if size x (x2 - x1) stays 1 difference when changing y-value
 */
#include "../bits/stdc++.h"

using namespace std;

class Solution {
public:
    int calculateArea(int x1, int y1, int x2, int y2) {
        int minY = min(y1, y2);
        return abs(x2 - x1) * minY;
    }

    /* solution 1 -> Time Limit Exceeded
    O(n^2), where n <= 10^5 ~ 100,000 ~ about 3~4 seconds

    int maxArea(vector<int>& height) {
        int ans = 0;
        for(int x1 = 0; x1 < height.size() - 1; x1++) {
            for(int x2 = x1 + 1; x2 < height.size(); x2++) {
                ans = max(ans, calculateArea(x1, height[x1], x2, height[x2]));
            }
        }
        return ans;
    }
    */

    /* solution 2 -> Two pointer
    */
    int maxArea(vector<int> &height) {
        int left = 0, right = height.size() - 1, ans = 0;

        while (left < right) {
            int area = calculateArea(left, height[left], right, height[right]);
            ans = max(ans, area);

            if (height[left] <= height[right]) left++;
            else right--;
        }

        return ans;
    }
};


int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    Solution s = *new Solution();
    vector<int> vector;
    vector.emplace_back(2);
    vector.emplace_back(3);
    vector.emplace_back(10);
    vector.emplace_back(5);
    vector.emplace_back(7);
    vector.emplace_back(8);
    vector.emplace_back(9);
    cout << s.maxArea(vector) << '\n';
    return 0;
}