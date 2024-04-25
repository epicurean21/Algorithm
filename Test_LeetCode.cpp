#include "stack"
#include "iostream"

using namespace std;

class Solution {
public:
    static bool isOpen(char &c) {
        return c == '(' || c == '{' || c == '[';
    }

    static bool isRightCouple(char &c1, char &c2) {
        if (c1 == '(') {
            if (c2 == ')') return true;
            else return false;
        } else if (c1 == '{') {
            if (c2 == '}') return true;
            else return false;
        } else if (c1 == '[') {
            if (c2 == ']') return true;
            else return false;
        }
        return false;
    }

    bool isValid(string s) {
        stack<char> st;
        for (char c: s) {
            if (st.empty()) {
                if (!isOpen(c)) {
                    return false;
                }
                st.push(c);
            } else {
                char last = st.top();
                if (!isOpen(c)) {
                    if (!isRightCouple(last, c)) {
                        return false;
                    } else {
                        st.pop();
                    }
                } else {
                    st.push(c);
                }
            }
        }

        if (!st.empty()) {
            return false;
        }

        return true;
    }
};

int main() {
    cin.tie(nullptr)->ios::sync_with_stdio(false);

    Solution solution = *new Solution();
    cout << solution.isValid("([])") << "\n";

    return 0;
}