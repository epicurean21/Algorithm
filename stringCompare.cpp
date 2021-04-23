// 프로그래머스 문자열 압축
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;


int max(int a, int b){
    return a > b? a : b;
}
vector<int> citations = {3, 0, 6, 1, 5};
int solution2() {
    int answer = 0;
    int min_count = citations[*min_element(citations.begin(), citations.end())];
    int max_count = citations[*max_element(citations.begin(), citations.end())];
    for(int i = min_count; i = max_count; i++) {
        int cnt_over = 0;
        int cnt_under = 0;
        for(int j = 0; j < citations.size(); j++) {
            if(citations[j] == i) {
                cnt_over++;
                cnt_under++;
            }else if(citations[j] > i) {
                cnt_under++;
            }else{
                cnt_over++;
            }
        }
        if(cnt_over == i && cnt_under == i)
            answer = max(answer, i);
    }

    return answer;
}

int solution(string s) {
    int answer = s.length();
    if (answer == 1)
        return 1;
    for (int i = 1; i <= s.length() / 2; i++) {
        int count = 1;
        string f = s.substr(0, i);
        cout << "f: " << f << "\n";
        string cmp, cp;

        for (int j = i; j < s.length(); j += i) {
            cmp = s.substr(j, i);
            cout << "cmp: " << cmp << "\n";
            if (!f.compare(cmp)) // 비교 문자가 같으면 count 개수 증가
                count++;
            else {
                if (count == 1) {
                    cp += f;
                    f = cmp;
                } else {
                    cp = cp + to_string(count) + f;
                    f = cmp;
                    count = 1;
                }
            }

            if (j + i >= s.length()) {
                if (count != 1) {
                    cp = cp + to_string(count) + f;
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

    string str = "abcds";
    string str2 = "abcds";

    cout << solution2() << "\n";
    return 0;
}
