#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;
vector<vector<int>> g;
map<string, int> dfs;
int N, a, b, cnt;
string ans, str;
vector<bool> chk;

void DFS(int cur) {
    chk[cur] = true;
    str += (cur + '0');

    if (str.length() == N) {
        dfs[str] = cnt++;
        str.pop_back();
        return;
    }

    for (int i = 0; i < g[cur].size(); i++) {
        int next = g[cur][i];
        if (chk[next]) continue;
        chk[next] = true;
        DFS(next);
        chk[next] = false;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    chk.resize(N + 1);
    g.resize(N + 1);
    for (int i = 0; i < N; i++) {
        cin >> a >> b;
        g[a].push_back(b);
    }
    DFS(1);
    char tmp;
    for (int i = 0; i < N; i++) {
        cin >> tmp;
        ans += tmp;
    }
    for (auto f = dfs.begin(); f != dfs.end(); f++) {
        cout << f->first << " " << f->second << "\n";
    }
    if (dfs.count(ans))
        cout << "1\n";
    else
        cout << "0\n";

    return 0;
}