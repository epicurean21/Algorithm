#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std;
int idx, cnt;
map<string, int> m, cntGems;
vector<string> gems = {"DIA", "RUBY", "RUBY", "DIA", "EMERALD", "DIA", "SAPPHIRE", "DIA", "SAPPHIRE", "RUBY",
                       "EMERALD"};

vector<int> solution() {
    vector<int> answer;
    for (int i = 0; i < gems.size(); i++) {
        if (!m.count(gems[i])) {
            m[gems[i]] = idx++;
            cnt++;
        }
    }

    int l = 0, r = 0, curCnt = 1, len = 100001, a = 0, b = 0;
    cntGems[gems[0]] = 1;
    while (l <= r) {
        if (curCnt < cnt) {
            if (!cntGems[gems[r + 1]]) { // 다음꺼가 없던거
                cntGems[gems[r + 1]] = 1;
                curCnt++;
            } else {
                cntGems[gems[r + 1]]++;
            }
            r++;
        } else if (curCnt == cnt) { // 찾는거 다 있음
            if (len > (r - l)) {
                a = l;
                b = r;
                len = r - l;
            }

            if (cntGems[gems[l]] == 1) curCnt--;
            cntGems[gems[l]]--;
            l++;
        } else
            break;

        if (r == gems.size()) break;
    }

    answer.emplace_back(a + 1);
    answer.emplace_back(b + 1);
    return answer;
}

int main() {
    vector<int> ans = solution();
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] << " ";
    }
    cout << '\n';
    return 0;
}