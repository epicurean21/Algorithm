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
/*

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
*/

/*
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int find(string str) {
    if (str == "one") {
        return 1;
    } else if (str == "two")
        return 2;
    else if (str == "zero")
        return 0;
    else if (str == "three")
        return 3;
    else if (str == "four")
        return 4;
    else if (str == "five")
        return 5;
    else if (str == "six")
        return 6;
    else if (str == "seven")
        return 7;
    else if (str == "eight")
        return 8;
    else if (str == "nine")
        return 9;
    else
        return -1;
}

int solution(string s) {
    int answer = 0;
    vector<int> tmp;
    int num = 0;
    string str = "";
    for (int i = 0; i < s.length(); i++) {
        if ((s[i] - '0') >= 0 && (s[i] - '0') <= 9) {
            tmp.emplace_back(s[i] - '0');
            continue;
        }
        str += s[i];
        num = find(str);
        if (num >= 0) {
            tmp.emplace_back(num);
            str = "";
        }
    }
    int idx = tmp.size() - 1;
    for (int i = 0; i < tmp.size(); i++) {
        answer += ((int) tmp[i] * (int) pow(10, idx));
        idx--;
    }
    return answer;
}

int main() {
    string tmp;
    cin >> tmp;
    cout << solution(tmp) << '\n';
}

 */

/*
 * 3번
 * 구현, 명령어 입력받아서 현재 표를 변경하는거
 * 효율성을 위해 실제 삭제가 아닌 행의 삭제 여부, 최근 삭제 인덱스를 갖고있는게 좋아보임 (스택으로 !)
 * U X 현재에서 X칸 위
 * D X x칸 아래
 * C 현재 삭제, 아래꺼 선택
 * Z 최근삭제 복구, 위치는 그대로
 */
#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;
int curUp, curDown; // 나보다 위에 지워진 수, 나보다 아래 지워진 수
vector<bool> isDeleted; // idx, 삭제여부

int findDelUp(int cur) {
    int tmp = 0;
    for (int i = 0; i <= cur; i++) {
        if (isDeleted[i])
            tmp++;
    }
    return tmp;
}

int findDelDown(int cur) {
    int tmp = 0;
    for (int i = cur; i < isDeleted.size(); i++) {
        if (isDeleted[i])
            tmp++;
    }
    return tmp;
}

string solution(int n, int k, vector<string> cmd) {
    string answer = "";

    stack<int> st; // 삭제 pos
    isDeleted.resize(n);
    int cur = k;
    int curSize = n - 1;
    // n 행 개수 k 시작 열 (0~)
    for (int i = 0; i < cmd.size(); i++) {
        char c = cmd[i][0];
        if (c == 'U') {
            int pos = (int) (cmd[i][2] - '0');
            cur -= (pos + curUp);  // 현 위치에서 원하는 값 + 지워진 수 많큼 이동
            if (cur < 0)
                cur = 0;
            curDown += curUp;
            curUp = findDelUp(cur);
        } else if (c == 'D') {
            int pos = (int) (cmd[i][2] - '0');
            cur += (pos + curDown); //
            if (cur > curSize)
                cur = curSize;
            curUp += curDown;
            curDown = findDelDown(cur);
        } else if (c == 'C') {
            st.push(cur); // 현재꺼 삭제;
            isDeleted[cur] = true;
            cur++;
            curUp++;
            if (cur > curSize) // 즉 맨 마지막 꺼 였다
                cur = curSize;
            if (isDeleted[cur]) { // 현재 위치는 지워진애다
                for (int i = cur; i < curSize; i++) {
                    if (!isDeleted[i])
                        cur = i;
                }
            }

        } else if (c == 'Z') {
            if (st.empty()) continue;
            int idx = st.top();
            isDeleted[idx] = false;
            st.pop();
            if (cur > idx) {
                curUp++;
            } else
                curDown++;
        }

    }

    for (int i = 0; i < n; i++) {
        if (isDeleted[i])
            answer += 'X';
        else
            answer += 'O';
    }
    return answer;
}

int main() {
    vector<string> cmd = {"D 2", "C", "U 3", "C", "D 4", "C", "U 2", "Z", "Z", "U 1", "C"};
    int n = 8, k = 2;
    cout << solution(n, k, cmd) << '\n';
}

/* 2번
#include <string>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include <iostream>

using namespace std;
vector<queue<pair<int, int>>> vec(5);
int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};
bool been[5][5][5];

void init(int idx) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            been[idx][i][j] = false;
        }
    }
}

vector<int> solution(vector<vector<string>> places) {
    vector<int> answer;
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            for (int k = 0; k < 5; k++)
                if (places[i][j][k] == 'P')
                    vec[i].push({k, j});

    for (int i = 0; i < 5; i++) {
        bool isOkay = true; // 해당 강의실

        while (!vec[i].empty()) {
            if (!isOkay) break;

            init(i); // i번째 강의실 방문 여부

            queue<pair<int, int>> cur; // 현자 사람
            cur.push(vec[i].front());
            int x = vec[i].front().first; // 사람 위치
            int y = vec[i].front().second;
            been[i][y][x] = true;
            vec[i].pop();
            bool tmp = true; // 해당 사람 여부
            while (!cur.empty()) { // bfs
                if (!tmp)
                    break;
                int cx = cur.front().first; // 현 위치
                int cy = cur.front().second;
                been[i][cy][cx] = true;
                cur.pop();

                for (int k = 0; k < 4; k++) {
                    int nx = cx + dx[k];
                    int ny = cy + dy[k];
                    if (nx < 0 || nx >= 5 || ny < 0 || ny >= 5) continue; // 범위 밖
                    if (places[i][ny][nx] == 'X') continue; // 가림막
                    if (been[i][ny][nx]) continue; // 방문함
                    if ((abs(x - nx) + abs(y - ny)) > 2) continue; // 이미 맨하탄 2 넘음
                    been[i][ny][nx] = true;
                    if (places[i][ny][nx] == 'P') tmp = false; // 사람이면 실패
                    cur.push({nx, ny});
                }
            }
            isOkay = tmp;
        }

        if (isOkay)
            answer.emplace_back(1);
        else
            answer.emplace_back(0);
    }

    return answer;
}

int main() {
    vector<string> cmd = {"D 2", "C", "U 3", "C", "D 4", "C", "U 2", "Z", "Z", "U 1", "C"};
    vector<vector<string>>
            places = {{"POOOP", "OXXOX", "OPXPX", "OOXOX", "POXXP"},
                      {"POOPX", "OXPXP", "PXXXO", "OXXXO", "OOOPP"},
                      {"PXOPX", "OXOXP", "OXPXX", "OXXXP", "POOXX"},
                      {"OOOXX", "XOOOX", "OOOXX", "OXOOX", "OOOOO"},
                      {"PXPXP", "XPXPX", "PXPXP", "XPXPX", "PXPXP"}};
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < places[i].size(); j++) {
            for (int k = 0; k < places[i][j].length(); k++)
                if (places[i][j][k] == 'P')
                    vec[i].push({k, j});
        }
    }

    solution(places);
}
*/


/*
 * 카카오 4번
#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>

using namespace std;
vector<vector<pair<pair<int, int>, int>>> map;
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
int dist[1001];
bool isTrap[1001];
bool chk[1001][1001];
priority_queue<int, vector<int>, greater<int>> ans;

bool cmp(pair<pair<int, int>, int> a, pair<pair<int, int>, int> b) {
    if (a.first.first > b.first.first) // 일단 목적지 순서대로
        return false;
    else if (a.first.first == b.first.first) { // 같은 목적지다
        if (a.first.second > b.first.second) // 근데 가는 cost가 크면 false
            return false;
        else
            return true;
    }
    return true;
}

void init(int n) {
    for (int i = 1; i <= n; i++)
        dist[i] = INT32_MAX;
}

void init_chk(int cur) {
    for (int i = 0; i < map[cur].size(); i++)
        chk[cur][i] = false;
}

void toggle(int cur, int n) {
    for (int i = 0; i < map[cur].size(); i++) {
        map[cur][i].second *= -1; // 방향 바꿔줌
    }
    for (int i = 1; i <= n; i++) {
        if (i == cur) continue;
        for (int j = 0; j < map[i].size(); j++) {
            if (map[i][j].first.first == cur)
                map[i][j].second *= -1;
        }
    }
}

int solution(int n, int start, int end, vector<vector<int>> roads, vector<int> traps) {
    int answer = 0;
    map.resize(n + 1);
    for (int i = 0; i < roads.size(); i++) {
        int from = roads[i][0];
        int there = roads[i][1];
        int cost = roads[i][2];
        map[from].push_back({{there, cost}, 1});
        map[there].push_back({{from, cost}, -1});
    }
    for (int i = 0; i < traps.size(); i++)
        isTrap[traps[i]] = true;

    init(n);
    for (int i = 1; i <= n; i++)
        sort(map[i].begin(), map[i].end(), cmp);

    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int cur = pq.top().second;
        int cost = pq.top().first;
        pq.pop();

        if (cur == end) {
            answer = min(dist[cur], cost);
            break; // min-pq 가중치가 가장 작을때 도착했을 것
        }

        // 트렙에 걸렸다
        if (isTrap[cur])
            toggle(cur, n);

        init_chk(cur);
        for (int i = 0; i < map[cur].size(); i++) {
            int next = map[cur][i].first.first;
            int next_cost = map[cur][i].first.second;
            int isPossible = map[cur][i].second;

            if (isPossible == -1) continue; // 방향이 갈 수 없는거

            if (chk[cur][next]) continue;
            chk[cur][next] = true;

            int total_cost = cost + next_cost;
            dist[next] = min(total_cost, dist[next]);
            pq.push({total_cost, next});
        }
    }

    return answer;
}

int main() {
    int n = 4, start = 1, end = 4;
    vector<vector<int>> roads = {{1, 2, 1},
                                 {1, 2, 4},
                                 {3, 2, 1},
                                 {2, 4, 1}};
    vector<int> traps = {2, 3};
    cout << solution(n, start, end, roads, traps);


    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < map[i].size(); j++) {
            cout << "from: " << i << ", there: " << map[i][j].first.first << ", cost: " << map[i][j].first.second
                 << '\n';
        }
    }
}
*/