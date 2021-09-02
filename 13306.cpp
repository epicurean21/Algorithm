/**
 * Offline Query
 * Disjoint Set & Union Find
 *
 * 오프라인 쿼리
 * [역순서] 특정 간선을 생성한 뒤
 * 특정 노드 쌍간의 연결성을 판별하는 것

 * [순서] 특정 간선이 제거 되기 전에
 * 특정 노드 쌍간의 연결성을 판별하는 것
 *
 * 두 쿼리는 동일한 답을 산출
 *
 * 트리의 서브 트리는 연결 컴포넌트임
 */

#include <iostream>
#include <stack>

using namespace std;
#define MAX 200001
int N, Q, a, x, c, b, d, cnt;
int p[MAX];
stack<pair<int, pair<int, int>>> query;
stack<string> ans;

int find(int a) {
    if (p[a] == a)
        return a;
    return p[a] = find(p[a]);
}

void merge(int a, int b) {
    int aa = find(a);
    int bb = find(b);

    p[aa] = bb;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> Q;

    for (int i = 1; i <= N - 1; i++) {
        cin >> a;
        p[i + 1] = a;
    }
    cnt = N - 1 + Q;
    while (cnt--) {
        cin >> x;
        if (x) {
            cin >> c >> d;
            query.push({1, {c, d}});
        } else {
            cin >> b;
            query.push({0, {b, p[b]}});
            p[b] = b; // 경로를 삭제 걍 자기자신이 그룹으로
        }
    }

    while (!query.empty()) { // 질의 역순
        int queryIndex = query.top().first;

        if (queryIndex) { // 질의 1
            pair<int, int> cd = query.top().second;
            if (find(cd.first) == find(cd.second))
                ans.push("YES");
            else
                ans.push("NO");
        } else
            merge(query.top().second.second, query.top().second.first);
        query.pop();
    }

    while (!ans.empty()) {
        cout << ans.top() << "\n";
        ans.pop();
    }
    return 0;
}