/*
 * Strongly Connected Component (강한 연결 요소)
 * 알고리즘 방법
 * Phase 1: DFS를 한번 수행한다. 수행하며 더 이상 갈 곳이 없는 vertex를 순서대로 stack (finished stack)에 넣는다
 * Phase 2: finished stack의 기준으로 pop 하며 반대 간선 그래프에 대한 (Graph transpose) DFS 수행한다.
 * starting vertex가 각 SCC의 대표가 된다.
 */

#include <iostream>
#include <stack>
#include <vector>

using namespace std;
vector<vector<int>> G;
vector<vector<int>> Gt; // Graph G의 transpose
vector<bool> visited;
vector<int> SCC; // SCC 요소 저장
int V, E, A, B;
stack<int> finished_stack;

void init() {
    for (int i = 1; i <= V; i++)
        visited[i] = false;
}

void dfs_phase1(int v) {
    if (visited[v]) return;
    visited[v] = true;

    for (int i = 0; i < G[v].size(); i++)
        if (!visited[G[v][i]])
            dfs_phase1(G[v][i]);

    finished_stack.push(v);
}

void dfs_phase2(int v, int group_number) {
    if (visited[v]) return;
    visited[v] = true;
    SCC[v] = group_number;

    for (int i = 0; i < Gt[v].size(); i++)
        if (!visited[Gt[v][i]])
            dfs_phase2(Gt[v][i], group_number);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> V >> E;
    G.resize(V + 1);
    Gt.resize(V + 1);
    visited.resize(V + 1);
    SCC.resize(V + 1);

    for (int i = 0; i < E; i++) {
        cin >> A >> B;
        G[A].emplace_back(B);
        Gt[B].emplace_back(A);
    }

    for (int i = 1; i <= V; i++)
        if (!visited[i])
            dfs_phase1(i);

    init();

    int group_count = 1;

    while (!finished_stack.empty()) {
        if (!visited[finished_stack.top()])
            dfs_phase2(finished_stack.top(), group_count++);
        finished_stack.pop();
    }

    cout << group_count - 1 << "\n";
    init();
    for (int i = 1; i <= V; i++) {
        if (visited[i]) continue;
        int cur_group = SCC[i];
        visited[i] = true;
        cout << i << " ";
        for (int j = i + 1; j <= V; j++) {
            if (cur_group == SCC[j] && !visited[j]) {
                visited[j] = true;
                cout << j << " ";
            }
        }
        cout << "-1\n";
    }

    return 0;
}