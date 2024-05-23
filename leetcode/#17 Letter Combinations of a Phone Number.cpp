#include "../bits/stdc++.h"

using namespace std;

class Solution {
public:
    vector<char> numbers[10];
    vector<string> answers;
    string input;

    void backtracking(string digits, string mappedNumbers, int idx) {
        if (idx == input.length()) {
            answers.emplace_back(mappedNumbers);
            return;
        };

        int digit = digits[idx] - '0';
        for (int i = 0; i < numbers[digit].size(); i++) {
            char mappedNumber = numbers[digit][i];
            backtracking(digits, mappedNumbers + mappedNumber, idx + 1);
        }
    }

    void initialize(string digits) {
        input = digits;
        char alphabet = 'a';
        for (int i = 2; i <= 9; i++) {
            int k = 3;
            if (i == 7 || i == 9)
                k = 4;
            for (int j = 0; j < k; j++) {
                numbers[i].emplace_back(alphabet);
                alphabet++;
            }
        }
    }

    vector<string> letterCombinations(string digits) {
        initialize(digits);
        backtracking(digits, "", 0);
        return answers;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    Solution s = *new Solution();
    s.letterCombinations("23");
    return 0;
}