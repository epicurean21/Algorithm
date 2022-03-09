/**
 * 14466 소가 길을 건너간 이유 6
 * 그래프 이론, 그래프 탐색, BFS
 */
#include <iostream>
#include <map>
#include <vector>

using namespace std;
#define MAX 101
bool chk[MAX][MAX], cowMap[MAX][MAX];
int N, K, R, r, c, rr, cc, dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};
vector<pair<int, int>> cows;
map<pair<pair<int, int>, pair<int, int>>, int> roads;
map<pair<pair<int, int>, pair<int, int>>, int> ans;

void init() {
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            chk[i][j] = false;
}

void bfs(int x, int y, bool isOverRoad) {
    chk[y][x] = true;
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx < 1 || nx > N || ny < 1 || ny > N) continue;
        if (!cowMap[ny][nx]) continue;
        if (chk[ny][nx]) continue;
        chk[ny][nx] = true;

        if (isOverRoad) { // 이미 길 건너야 함
            if ((ans.find({{x,  y},
                           {nx, ny}}) != ans.end())
                || (ans.find({{nx, ny},
                              {x,  y}}) != ans.end())) { // 이미 정답에 있음
                bfs(nx, ny, true);
            } else { // 정답에 없음
                ans.insert({{{x, y}, {nx, ny}}, (int) ans.size() + 1}); // 정답에 추가
                bfs(nx, ny, true);
            }
        } else { // 길 건너기 전
            if (roads.find({{x,  y},
                            {nx, ny}}) != roads.end()) { // 길 건너야 하는 사이
                if ((ans.find({{x,  y},
                               {nx, ny}}) != ans.end())
                    || (ans.find({{nx, ny},
                                  {x,  y}}) != ans.end())) { // 정답에 이미 있음
                    bfs(nx, ny, false);
                } else { // 정답에 없음
                    //cout << "x: " << x << " y: " << y << " nx: " << nx << " ny: " << ny << '\n';
                    ans.insert({{{x, y}, {nx, ny}}, (int) ans.size() + 1});
                    bfs(nx, ny, true);
                }
            } else { // 길 안건너도 되는 사이
                //cout << "no answer, " << "x: " << x << " y: " << y << " nx: " << nx << " ny: " << ny << '\n';
                bfs(nx, ny, false);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> K >> R;
    for (int i = 0; i < R; i++) {
        cin >> r >> c >> rr >> cc;
        roads.insert({{{c, r}, {cc, rr}}, i});
        roads.insert({{{cc, rr}, {c, r}}, i + R});
    }

    for (int i = 0; i < K; i++) {
        cin >> r >> c;
        cows.emplace_back(c, r);
        cowMap[r][c] = true;
    }

    for (int i = 0; i < K; i++) {
        int x = cows[i].first;
        int y = cows[i].second;
        init();
        bfs(x, y, false);
    }

    for (auto & an : ans) {
        cout << "r: " << an.first.first.second << " , c: " << an.first.first.first << ", ans rr: "
             << an.first.second.second << " , cc: " << an.first.second.first << '\n';
    }

    cout << ans.size() << '\n';
    return 0;
}