#include <iostream>
#include <stack>
#include <vector>
#include <set>

using namespace std;

string solution(int n, int k, vector<string> cmd) {
    string answer = "";
    for (int i = 0; i < n; i++) {
        answer += 'X';
    }

    set<int> chart;
    stack<int> st;

    for (int i = 0; i < n; i++)
        chart.insert(i);

    auto cur = chart.find(k);

    for (auto &c : cmd) {
        if (c[0] == 'D') {
            string move = "";
            for (int i = 2; i < c.size(); i++)
                move += c[i];

            int move_int = stoi(move);
            while (move_int--) {
                if (next(cur) == chart.end())
                    break;
                cur = next(cur);
            }
        } else if (c[0] == 'U') {
            string move = "";
            for (int i = 2; i < c.size(); i++)
                move += c[i];

            int move_int = stoi(move);
            while (move_int--) {
                if (prev(cur) == chart.begin()) {
                    cur = prev(cur);
                    break;
                }
                cur = prev(cur);
            }
        } else if (c[0] == 'C') {
            st.push(*cur);
            auto cur_pos = cur;
            if (next(cur) == chart.end())
                cur--;
            else
                cur = next(cur);
            chart.erase(cur_pos);
        } else if (c[0] == 'Z') {
            chart.insert(st.top());
            st.pop();
        }
    }

    for (auto &i : chart)
        answer[i] = 'O';

    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n, k;
    vector<string> cmd;
    cin >> n >> k;
    cmd.emplace_back("D 2");
    cmd.emplace_back("C");
    cmd.emplace_back("U 3");
    cmd.emplace_back("C");
    cmd.emplace_back("D 4");
    cmd.emplace_back("C");
    cmd.emplace_back("U 2");
    cmd.emplace_back("Z");
    cmd.emplace_back("Z");
    cmd.emplace_back("U 1");
    cmd.emplace_back("C");
    cout << solution(n, k, cmd) << "\n";
    return 0;
}