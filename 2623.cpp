#include <iostream>
#include <vector>
#include <queue>

using namespace std;
#define MAX 1001

int N, P, K, tmp, singer, ind[MAX];
vector<vector<int>> graph(MAX);
vector<int> ans;
queue<int> q;
bool chk[MAX];

void find() {
    while (!q.empty()) {
        int cur = q.front();
        ans.push_back(cur);
        chk[cur] = true;
        q.pop();
        for (int i = 0; i < graph[cur].size(); i++) {
            int next = graph[cur][i];
            if (chk[next]) continue;
            ind[next] -= 1;
            if (ind[next] == 0)
                q.push(next);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> P;
    for (int i = 0; i < P; i++) {
        cin >> K;
        for (int j = 0; j < K; j++) {
            cin >> singer;
            if (j != 0) {
                ind[singer]++;
                graph[tmp].push_back(singer);
            }
            tmp = singer;
        }
    }
    for (int i = 1; i <= N; i++) {
        if (ind[i] == 0)
            q.push(i);
    }

    find();

    if (ans.size() < N)
        cout << "0\n";
    else
        for (int i = 0; i < ans.size(); i++)
            cout << ans[i] << '\n';
    return 0;
}