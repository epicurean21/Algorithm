#include <iostream>
#include <vector>
#include <queue>

using namespace std;
#define MAX 300001

vector<vector<int>> map;
priority_queue<int, vector<int>, greater<int>> ans;
int N, M, K, X, A, B;
bool been[MAX];

void bfs(int start, int dis) {
    been[start] = true;
    queue<pair<int,int>> q;
    q.push({start, dis});
    while(!q.empty()) {
        int cur = q.front().first;
        int dist = q.front().second;
        q.pop();
        if(dist == K) {
            ans.push(cur);
            continue;
        }
        for(int i = 0; i < map[cur].size(); i++) {
            int next = map[cur][i];
            if(!been[next]) {
                been[next] = true;
                q.push({next, dist + 1});
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> M >> K >> X;
    map.resize(N + 1);
    for (int i = 0; i < M; i++) {
        cin >> A >> B;
        map[A].push_back(B);
    }
    bfs(X, 0);
    if(!ans.empty()) {
        while(!ans.empty()) {
            cout << ans.top() << "\n";
            ans.pop();
        }
    }
    else
        cout << "-1\n";
    return 0;
}