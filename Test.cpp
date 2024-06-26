#include "bits/stdc++.h"

using namespace std;

#define ERROR "Error!\n"
#define UNDER_SCORE '_'
string input, result;
stack<char> st;

bool isCapitalLetter(char c) {
    return 'A' <= c && c <= 'Z';
}

char convertCharacter(bool is_capital, char c) {
    if (is_capital) return (c - 'A' + 'a');
    else return (c - 'a' + 'A');
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> input;
    if (input[0] == UNDER_SCORE || input[input.length() - 1] == UNDER_SCORE) {
        cout << ERROR;
        return 0;
    }

    if (input.find(UNDER_SCORE) == string::npos && isCapitalLetter(input[0])) {
        cout << ERROR;
        return 0;
    }

    bool is_java = false, is_c = false;
    for (char c: input) {
        if (!st.empty() && st.top() == UNDER_SCORE && c == UNDER_SCORE) {
            cout << ERROR;
            return 0;
        }
        if (c == UNDER_SCORE) {
            if (is_java) {
                cout << ERROR;
                return 0;
            }
            is_c = true;
            st.push(c);
            continue;
        }

        if (isCapitalLetter(c)) {
            if (is_c) {
                cout << ERROR;
                return 0;
            }
            is_java = true;
            st.push(c);
            result += UNDER_SCORE;
            result += convertCharacter(true, c);
            continue;
        }

        if (!st.empty() && st.top() == UNDER_SCORE) {
            result += convertCharacter(false, c);
            st.push(c);
            continue;
        }

        result += c;
    }
    cout << result << '\n';

    return 0;
}