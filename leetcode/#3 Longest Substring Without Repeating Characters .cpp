/**
 * leetcode #3
 * Longest Substring Without Repeating Characters
 * Difficulty: MEDIUM
 * -
 * use map to parse String
 */
#include "iostream"
#include "unordered_map"

using namespace std;

class Solution {
private:
    int ans = INT_MIN;
    unordered_map<char, int> characterSet;

public:
    int lengthOfLongestSubstring(string s) {
        if (s.empty()) return 0;
        int i = 0, j = 0, ans = INT_MIN;
        while (j < s.length()) {
            characterSet[s[j]]++;
            if (characterSet.size() == j - i + 1) {
                ans = max(ans, j - i + 1);
            } else if (characterSet.size() < j - i + 1) {
                while (characterSet.size() < j - i + 1) {
                    characterSet[s[i]]--;
                    if (characterSet[s[i]] == 0) characterSet.erase(s[i]);
                    i++;
                }
            }
            j++;
        }
        return ans;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    Solution solution;

    string s;
    while (cin >> s) {
        if (s == "0") exit(0);
        cout << solution.lengthOfLongestSubstring(s) << '\n';
    }

    return 0;
}