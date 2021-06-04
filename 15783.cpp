#include<iostream>
#include<vector>
#include<algorithm>
#include<stack>

using namespace std;
#define MAX 100001

vector<int> v[MAX];
vector<pair<int, int>> u;
int ind[MAX];
bool visit[MAX];
int n, m;
stack<int> s;

void dfs(int x) {
    if (visit[x])
        return;
    visit[x] = true;
    for (auto i : v[x]) {
        if (visit[i])
            continue;
        dfs(i);
    }
    s.push(x);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n >> m;
    int a, b;
    int cnt = 0;
    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        v[a].push_back(b);
    }

    for (int i = 0; i < n; i++)
        if (!visit[i])
            dfs(i);

    for (int i = 0; i < n; i++)
        visit[i] = false;

    while (!s.empty()) {
        if (!visit[s.top()]) {
            dfs(s.top());
            cnt++;
        }
        s.pop();
    }
    cout << cnt << "\n";
    return 0;
}