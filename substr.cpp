/*
 * substr == string 라이브러리 안에 있는 함수
 * string str = "abcd"
 * string tmp = str.substr(0, 1)  ---> ab
 */

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

int T, N;
string str;
vector<string> m;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> T;
    while (T--) {
        m.clear();
        cin >> N;
        bool flag = true;
        for (int i = 0; i < N; i++) {
            cin >> str;
            m.push_back(str);
        }
        sort(m.begin(), m.end());
        for (int i = 0; i < N - 1; i++) {
            string cur = m[i];
            string next = m[i + 1];
            if (next.length() > cur.length()) {
                if (cur == next.substr(0, cur.length())) {
                    flag = false;
                    break;
                }
            }
        }
        if (flag) {
            cout << "YES\n";
        } else cout << "NO\n";
    }

    string test1 = "abcd";
    string test2 = "abcdefg";
    string test3 = "bcd";
    cout << test2.substr(0, test1.length()) << "\n";
    cout << test3.substr(0, test1.length()) << '\n';
    return 0;
}