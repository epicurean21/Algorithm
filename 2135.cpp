#include <iostream>
#include <string>

using namespace std;

int solution(string s) {
    int answer = s.length();
    if (answer == 1)
        return 1;
    for (int i = 1; i <= s.length() / 2; i++) {
        int count = 1;
        string f = s.substr(0, i);
        string cmp, cp;
        for (int j = i; j < s.length(); j += i) {
            cmp = s.substr(j, i);

            if (!f.compare(cmp)) // 비교 문자가 같으면 count 개수 증가
                count++;
            else {
                if (count == 1) {
                    cp += f;
                    f = cmp;
                } else {
                    cp = cp + "(" + to_string(count) + ")" + f;
                    f = cmp;
                    count = 1;
                }
            }

            if (j + i >= s.length()) {
                if (count != 1) {
                    cp = cp + "(" + to_string(count) + ")" + f;
                    break;
                } else {
                    cp = cp + s.substr(j);
                    break;
                }
            }
        }
        answer = (answer > cp.length()) ? cp.length() : answer;
    }

    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    string s;
    cin >> s;
    cout << solution(s) << '\n';

    return 0;
}