#include <vector>
#include <set>

using namespace std;

int n, ans;
vector<int> v;
set<int> avail;
bool visit[18];
int sheepCnt, wolfCnt;

void search(int i, vector<int> info, vector<vector<int>> edges) {

    v.push_back(i);
    if (!info[i]) {
        sheepCnt++;
        ans = ans >= sheepCnt ? ans : sheepCnt;
    } else
        wolfCnt++;
    for (int next : edges[i]) {
        avail.insert(next);
    }
    visit[i] = true;

    for (auto &next: avail) {
        if (visit[next]) continue;
        if (info[next] && sheepCnt <= wolfCnt + 1) continue;
        search(next, info, edges);

    }
    v.pop_back();
    for (int next : edges[i])
        avail.erase(next);
    visit[i] = false;

    if (!info[i])
        sheepCnt--;
    else
        wolfCnt--;
}

int solution(vector<int> info, vector<vector<int>> edges) {
    int answer;
    n = info.size();

    search(0, info, edges);
    answer = ans;
    return answer;
}