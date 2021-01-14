#include <iostream>
#include <string>
#include <stack>

using namespace std;

int ans, tmp = 1;
string str;
stack<char> st;
bool flag = false;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> str;

    for (int i = 0; i < str.length(); i++) {
        if (str[i] == '(' || str[i] == '[') {
            if (str[i] == '(') {
                tmp *= 2;
                st.push(str[i]);
            } else {
                tmp *= 3;
                st.push(str[i]);
            }
        } else { //닫는괄호
            if (str[i] == ')') {
                if (st.empty() || st.top() != '(') {
                    flag = true;
                    break;
                } else {
                    if (str[i - 1] == '(')
                        ans += tmp;
                    st.pop();
                    tmp /= 2;
                }
            } else if (str[i] == ']') {
                if (st.empty() || st.top() != '[') {
                    flag = true;
                    break;
                } else {
                    if (str[i - 1] == '[')
                        ans += tmp;
                    st.pop();
                    tmp /= 3;
                }
            }
        }
    }

    if (flag || !st.empty())
        cout << "0\n";
    else
        cout << ans << "\n";
    return 0;
}