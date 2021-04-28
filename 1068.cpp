#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int N, tmp, cnt, E;
vector<vector<int>> tree;
bool exist[51];

void dfs(int root) {
    exist[root] = false;
    for (int i = 0; i < tree[root].size(); i++) {
        int next = tree[root][i];
        if (!exist[next]) continue;
        exist[next] = false;
        dfs(next);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N;
    tree.resize(N);
    memset(exist, true, sizeof(exist));
    for (int i = 0; i < N; i++) {
        cin >> tmp;
        if (tmp == -1) continue;
        tree[tmp].push_back(i);
    }
    cin >> E;
    dfs(E);

    for (int i = 0; i < N; i++) {
        vector<int>::iterator it = tree[i].begin();
        for (int j = 0; j < tree[i].size(); j++) {
            if (tree[i][j] == E) {
                it = tree[i].erase(it);
                break;
            }
            it++;
        }
    }

    for (int i = 0; i < N; i++)
        if (exist[i] && tree[i].size() == 0)
            cnt++;
    cout << cnt << '\n';
    return 0;
}