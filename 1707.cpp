#include <iostream>
#include <vector>
#include <cstring>

using namespace std;
#define MAX 20001
int K, V, E, a, b;
vector<vector<int>> map;
int flag[MAX];
bool isBigraph;

void init() {
    map.clear();
    memset(flag, 0, sizeof(flag));
    isBigraph = true;
}

void dfs(int cur, int color) {
    flag[cur] = color;

    for (int next : map[cur]) {
        if (flag[next] == 0) {
            dfs(next, -1 * color);
        } else {
            if (flag[next] != -1 * color) {
                isBigraph = false;
                return;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> K;
    while (K--) {
        init();
        cin >> V >> E;

        map.resize(V + 1);
        for (int i = 0; i < E; i++) {
            cin >> a >> b;
            map[a].emplace_back(b);
            map[b].emplace_back(a);
        }

        for (int i = 1; i <= V; i++) {
            if (flag[i] == 0)
                dfs(i, 1);
        }


        if (isBigraph)
            cout << "YES\n";
        else
            cout << "NO\n";
    }
    return 0;
}