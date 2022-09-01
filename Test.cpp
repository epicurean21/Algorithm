/**
 * 14567 선수과목 (Prerequisite)
 * 위상정렬
 */
#include <iostream>
#include <vector>
#include <queue>

using namespace std;
#define MAX 1001
int N, M, A, B, indeg[MAX], ans[MAX];
queue<pair<int, int>> orders;
vector<vector<int>> courses;

void topological_sort() {
    while (!orders.empty()) {
        int cur = orders.front().first;
        int semester = orders.front().second;
        orders.pop();
        ans[cur] = semester;

        for (auto i: courses[cur]) {
            indeg[i]--;
            if (indeg[i] == 0) {
                orders.push({i, semester + 1});
            }
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> N >> M;
    courses.resize(N + 1);
    while (M--) {
        cin >> A >> B;
        courses[A].emplace_back(B);
        indeg[B]++;
    }

    for (int i = 1; i <= N; i++)
        if (indeg[i] == 0)
            orders.push({i, 1});

    topological_sort();
    for (int i = 1; i <= N; i++)
        cout << ans[i] << " ";
    cout << '\n';
    return 0;
}