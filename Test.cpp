#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

int solution(string s) {
    map<string, char> m;
    m["one"] = '1';
    m["two"] = '2';
    m["three"] = '3';
    m["four"] = '4';
    m["five"] = '5';
    m["six"] = '6';
    m["seven"] = '7';
    m["eight"] = '8';
    m["nine"] = '9';

    string answer = "";
    string str = "";
    for (int i = 0; i < s.length(); i++) {
        if (s[i] - '0' >= 0 && s[i] - '0' <= 9) {
            answer += s[i];
        } else {
            str += s[i];
            if (m.count(str)) {
                answer += m[str];
                str = "";
            }
        }
    }

    return stoi(answer);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cout << solution("one4seveneight") << "\n";
    return 0;
}