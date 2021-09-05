/**
 * Closing the Farm
 * - Data Structure
 * - Disjoint Set (Union-Find)
 * - Offline Query
 */
#include <iostream>
#include <vector>
#include <stack>
#include <string>

using namespace std;
#define MAX 200001
int N, M, p[MAX], a, b, cnt;
vector<vector<int>> map;
stack<int> query;
stack<string> ans;
bool chk[MAX];

int find(int a) {
    if (p[a] == a)
        return a;
    return p[a] = find(p[a]);
}

bool merge(int a, int b) {
    int aa = find(a);
    int bb = find(b);

    if (aa == bb)
        return false;
    else {
        p[aa] = bb;
        return true;
    }
}

void init(int N) {
    for (int i = 1; i <= N; i++)
        p[i] = i;

    map.clear();
    map.resize(N + 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;

    init(N);

    for (int i = 0; i < M; i++) {
        cin >> a >> b;
        map[a].emplace_back(b);
        map[b].emplace_back(a);
    }

    for (int i = 0; i < N; i++) {
        cin >> a;
        query.push(a);
    }

    while (!query.empty()) {
        cnt++;
        int cur = query.top();
        query.pop();
        for (int i = 0; i < map[cur].size(); i++) {
            int next = map[cur][i];
            if (chk[next])
                if (merge(cur, next))
                    cnt--;

            chk[cur] = true;
            if (cnt)
                ans.push("YES");
            else
                ans.push("NO");
        }
    }

    while (!ans.empty()) {
        cout << ans.top() << "\n";
        ans.pop();
    }

    return 0;
}