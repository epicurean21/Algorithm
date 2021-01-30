#include <iostream>
#include <vector>
#include <cstring>
#include <map>

using namespace std;
#define ll long long
#define MAX 100001

int V, chk[MAX], startP, ans;
vector<vector<pair<int, int>>> tree;
map<pair<int, int>, int> m;

void dfs(int cur, ll weight) {
    chk[cur] = true;
    if (ans < weight) {
        startP = cur;
        ans = weight;
    }
    for (int i = 0; i < tree[cur].size(); i++) {
        int next = tree[cur][i].first;
        int w = tree[cur][i].second;
        if (!chk[next]) {
            dfs(next, w + weight);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> V;
    tree.resize(V + 1);
    for (int i = 1; i <= V; i++) {
        int cur, next, weight;
        cin >> cur;
        while (cin >> next) {
            if (next == -1)
                break;
            cin >> weight;
            if (m.count({cur, next}) != 0 || m.count({next, cur}) != 0) continue;
            tree[cur].push_back({next, weight});
            tree[next].push_back({cur, weight});
            m.insert({{cur, next}, 1});
            m.insert({{next, cur}, 1});
        }
    }
    //루트에서부터 가장 먼 정점을 찾자.
    dfs(1, 0);
    //cout << startP << '\n';
    memset(chk, false, sizeof(chk));
    dfs(startP, 0);
    cout << ans << '\n';
    return 0;
}