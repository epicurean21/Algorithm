/**
 * leetcode #14
 * Longest Common Prefix
 * -
 * get longest common prefix
 * if there is no common prefix, return ""
 * Solution:
 * just compare between the shortest string and the longest string.
 * find the common prefix between two strings.
 */
#include "iostream"
#include "vector"

using namespace std;

class Solution {
private:
    int strsSize = 0;
    string n, m, ans;
public:
    string longestCommonPrefix(vector<string> &strs) {
        sort(strs.begin(), strs.end());
        strsSize = strs.size();
        n = strs[0];
        m = strs[strsSize - 1];
        ans = "";
        for (int i = 0; i < n.size(); i++) {
            if (n[i] == m[i]) { ans += n[i]; }
            else break;
        }
        return ans;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    Solution solution;
    vector<string> strs = {"flower", "flow", "flight"};
    cout << solution.longestCommonPrefix(strs) << "\n";
    strs = {"dog", "racecar", "car"};
    cout << solution.longestCommonPrefix(strs) << "\n";

    return 0;
}