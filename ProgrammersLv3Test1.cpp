#include <iostream>
#include <vector>
#include <map>
#include <queue>

using namespace std;

map<string, int> m;
queue<pair<string, int>> q;
vector<string> words = {"hot", "dot", "dog", "lot", "log", "cog"};

int main() {
    string begin, target;

    cin >> begin >> target;
    q.push({begin, 0});
    int answer = 0;
    bool exists = false;
    for (int i = 0; i < words.size(); i++) {
        if (target == words[i])
            exists = true;
    }
    if (exists) {
        int tmp = 0;
        m.insert({begin, tmp++});
        while (!q.empty()) {
            string cur = q.front().first;
            int cnt = q.front().second;
            q.pop();
            if (cur == target)
                answer = cnt;

            for (int i = 0; i < words.size(); i++) {
                int diffCnt = 0;
                string next = words[i];
                for (int j = 0; j < next.size(); j++)
                    if (cur[j] != next[j]) {
                        diffCnt++;
                    }
                if (diffCnt == 1) { // 다른게 한개라면 그걸로 변형해 보자
                    if (m.count(words[i]) != 0) continue;// 이미 q에 존재하면 무시
                    m.insert({words[i], tmp++});
                    q.push({words[i], cnt + 1});
                }
            }
        }
    } else
        answer = 0;
    cout << answer << "\n";
    return 0;
}