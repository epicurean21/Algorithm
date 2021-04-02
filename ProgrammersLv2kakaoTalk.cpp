#include <iostream>
#include <vector>
#include <map>

using namespace std;

string msg;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> msg;
    vector<int> answer;
    map<string, int> m;
    string cur = "";
    int cnt = 27;
    for (int i = 0; i < msg.length(); i++) {
        cur = "";
        cur += msg[i];
        if (i == msg.length() - 1) { // 마지막이다
            answer.push_back((cur[0] - 'A') + 1);
        } else {
            for (int j = i + 1; j < msg.length(); j++) {
                cur.push_back(msg[j]);
                if (m.count(cur) == 0) {//존재 X
                    m.insert({cur, cnt++});
                    cur.pop_back();
                    if (cur.length() > 1)
                        answer.push_back(m.find(cur)->second);
                    else
                        answer.push_back((cur[0] - 'A') + 1);
                    break;
                } else {
                    i = j;
                    if (j == msg.length() - 1) {
                        answer.push_back(m.find(cur)->second);
                        break;
                    }
                }
            }
        }
    }
    for (int i = 0; i < answer.size(); i++) {
        cout << answer[i] << " ";
    }
    return 0;
}