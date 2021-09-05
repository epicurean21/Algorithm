/**
 * Closing the Farm
 * - Data Structure
 * - Disjoint Set (Union-Find)
 * - Offline Query
 * 풀이: 질의를 역순으로 찾아가며, 각 컴포넌트의 개수를 세준다.
 * 정점을 추가할 때 그래프에 이미 추가된것만 merge
 * 거꾸로 접근하는 Offline Query가 포인트, 빈그래프에서 정점과 연결된 컴포넌트를 이어주면서
 * 총 컴포넌트 개수를 유지시키는 문제이다.
 *
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
        for (auto next : map[cur]) {
            if (chk[next] && merge(cur, next))
                cnt--;
        }

        chk[cur] = true;
        if (cnt == 1)
            ans.push("YES");
        else
            ans.push("NO");
    }

    while (!ans.empty()) {
        cout << ans.top() << "\n";
        ans.pop();
    }

    return 0;
}