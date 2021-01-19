#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define MAX 100010
int V, E, A, B, visitOrder[MAX], num = 1;
vector<vector<int>> map(MAX);
vector<pair<int, int>> ans;

int dfs(int cur, int pre) {
    visitOrder[cur] = num++;
    int min_visit_order = visitOrder[cur];

    for (int i = 0; i < map[cur].size(); i++) {
        int next = map[cur][i];
        if (next == pre)
            continue;
        if (visitOrder[next])
            min_visit_order = min(min_visit_order, visitOrder[next]);
        else {
            int tmp = dfs(next, cur);
            min_visit_order = min(tmp, min_visit_order);

            if (tmp > visitOrder[cur])
                ans.push_back({min(cur, next), max(cur, next)});
        }
    }

    return min_visit_order;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> V >> E;
    for (int i = 0; i < E; i++) {
        cin >> A >> B;
        map[A].push_back(B);
        map[B].push_back(A);
    }

    for (int i = 1; i <= V; i++)
        if (visitOrder[i] == 0)
            dfs(i, 0);

    sort(ans.begin(), ans.end());
    cout << ans.size() << "\n";
    for (int i = 0; i < ans.size(); i++)
        cout << ans[i].first << " " << ans[i].second << "\n";
    return 0;
}