/*
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
}*/

#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <cstring>

using namespace std;
#define MAX 26
const int INF = INT32_MAX;
int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};
int cost_map[MAX][MAX][4];
vector<vector<int>> board = {{0, 0, 1, 0, 1, 1, 0, 0, 0, 0},
                             {0, 0, 0, 0, 1, 0, 1, 1, 0, 1},
                             {1, 0, 0, 0, 0, 1, 1, 0, 1, 0},
                             {0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
                             {0, 0, 0, 0, 1, 0, 1, 0, 1, 1},
                             {0, 0, 1, 0, 1, 1, 0, 1, 0, 1},
                             {0, 1, 0, 0, 1, 0, 0, 0, 1, 0},
                             {1, 0, 0, 1, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 1, 0, 1, 0, 0},
                             {1, 0, 0, 0, 0, 0, 0, 0, 1, 0}
};

int solution() {
    int answer = INF;
    int sz = board[0].size();
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < sz; j++)
            for (int k = 0; k < sz; k++)
                cost_map[j][k][i] = INF;
    priority_queue<pair<pair<int, int>, pair<int, int>>, vector<pair<pair<int, int>, pair<int, int>>>, greater<pair<pair<int, int>, pair<int, int>>>> q;
    cost_map[0][0][0] = cost_map[0][0][1] = cost_map[0][0][2] = cost_map[0][0][3] = 0;
    q.push({{0, -1},
            {0, 0}}); // 비용, 방향, x, y
    while (!q.empty()) {
        int x = q.top().second.first;
        int y = q.top().second.second;
        int cur_dir = q.top().first.second;
        int cur_cost = q.top().first.first;
        q.pop();

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            int next_dir = i;
            if (nx < 0 || nx >= sz || ny < 0 || ny >= sz) continue;
            if (board[ny][nx] == 1) continue;
            if (cur_dir == -1 || cur_dir == next_dir) { // 시작점이거나 방향이 같음
                if (cost_map[ny][nx][next_dir] >= cur_cost + 100) {
                    cost_map[ny][nx][next_dir] = cur_cost + 100;
                    q.push({{cur_cost + 100, next_dir},
                            {nx,             ny}});
                }
            } else { // 방향이 다름
                if (cost_map[ny][nx][next_dir] >= cur_cost + 600) {
                    cost_map[ny][nx][next_dir] = cur_cost + 600;
                    q.push({{cur_cost + 600, next_dir},
                            {nx,             ny}});
                }
            }
        }
    }

    for (int i = 0; i < 4; i++)
        answer = min(cost_map[sz - 1][sz - 1][i], answer);
    return answer;
}

int main() {
    int tmp = solution();
    cout << tmp << '\n';
    return 0;
}

