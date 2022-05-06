#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;
map<string, int> report_cnt;
map<string, set<string>> report_map;
vector<int> solution(vector<string> id_list, vector<string> report, int k) {
    vector<int> answer;

    for (string s: report) {
        int blank = s.find(' ');
        string reporter = s.substr(0, blank);
        string abuser = s.substr(blank);

        if (report_map[reporter].find(abuser) == report_map[reporter].end()) {
            report_cnt[abuser]++;
            report_map[reporter].insert(abuser);
        }
    }
    for (string s: id_list) {
        int res = 0;
        for (string target: report_map[s]) {
            if (report_cnt[target] >= k) res++;
        }
        answer.emplace_back(res);
    }
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<string> id_list = {"muzi", "frodo", "apeach", "neo"};
    vector<string> report = {"muzi frodo","apeach frodo","frodo neo","muzi neo","apeach muzi"};
    int k = 2;

    vector<int> ans= solution(id_list, report, k);
    for(int i : ans) {
        cout << i << " ";
    }
}