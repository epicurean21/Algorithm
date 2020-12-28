#include <iostream>
#include <vector>

using namespace std;
#define MAX 1001
int N, M, u, v;
vector<vector<int>> graph;
bool been[MAX];

void dfs(int v) {
    been[v] = true;
    for(int i = 0; i < graph[v].size(); i++)
        if(!been[graph[v][i]])
            dfs(graph[v][i]);
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> M;
    graph.resize(N + 1);
    for(int i = 0; i < M; i++) {
        cin>> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    int cnt = 0;
    for(int i = 1; i <= N; i++) {
        if(!been[i]) {
            dfs(i);
            cnt++;
        }
    }
    cout << cnt << "\n";
    return 0;
}