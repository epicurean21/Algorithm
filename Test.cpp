#include "set"
#include "iostream"
#include "vector"
using namespace std;
set<int> int_set;

class Solution {
public:
    int removeDuplicates(vector<int> &nums) {
        for (int i = 0; i < nums.size(); i++) {
            if (int_set.count(nums[i])) nums[i] = INT32_MAX;
            else int_set.insert(nums[i]);
        }

        sort(nums.begin(), nums.end());
        return int_set.size();
    }
};

int main() {
    cin.tie(nullptr)->ios::sync_with_stdio(false);

    Solution solution = *new Solution();
    vector<int> nums = {0, 0, 1, 1, 1, 2, 2, 3, 3, 4};
    int ans = solution.removeDuplicates(nums);

    for (int i = 0; i < ans; i++) {
        cout << nums[i] << " ";
    }
    cout << "\n" << ans << "\n";

    return 0;
}