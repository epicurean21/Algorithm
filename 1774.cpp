/**
 * 1774 우주신과의 교감
 * 최소 신장 트리 (Minimum Spanning Tree)
 * 해결방안:
 * 모든 점들의 거리를 계산해서 거리들에 대한 list를 갖고있고, 이를 정렬해서
 * 짧은순으로 Kruskal Algorithm 을 통해 추가해나간다.
 * N이 1000이기에 가능한 해법 (O(n^2))
 * 중요한건, 거리 계산할 때 double 자료형을 넘어갈 수 있기에 long double을 사용해야한다.
 * 이거때매 계속틀림... 자료형이 제일 빡샌 문제. 나머지는 평이하다
 * Optimize 하는 방법은... union-find 에 대한 조건을 추가해서, m 개의 정보를 잘 활용하면 좀더 빠른 코드를 만들 수 있을것.
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
#define MAX 1001
#define ld long double
int n, m, x, y, par[MAX];
ld ans;
vector<pair<int, int>> cords;
vector<pair<ld, pair<int, int>>> dists;

void init(int num) {
    for (int i = 1; i <= num; i++) par[i] = i;
    cords.resize(num + 1);
}

int find(int num) {
    if (par[num] == num) return num;
    return par[num] = find(par[num]);
}

void merge(int a, int b) {
    a = find(a);
    b = find(b);
    if (a == b) return;

    par[a] = b;
}

long double calculateDistance(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cout.precision(2);
    cout << fixed;

    cin >> n >> m;
    init(n);

    for (int i = 1; i <= n; i++) cin >> cords[i].first >> cords[i].second;
    while (m--) {
        cin >> x >> y;
        if (find(x) == find(y)) continue;
        merge(x, y);
    }

    for (int i = 1; i <= n - 1; i++) {
        for (int j = i + 1; j <= n; j++) {
            pair<int, int> cur = cords[i];
            pair<int, int> next = cords[j];
            ld dist = calculateDistance(cur.first, cur.second, next.first, next.second);
            dists.push_back({dist, {i, j}});
        }
    }

    sort(dists.begin(), dists.end());
    for (auto &i: dists) {
        int cur = i.second.first;
        int next = i.second.second;
        ld dist = i.first;

        if (find(cur) == find(next)) continue;
        merge(cur, next);
        ans += dist;
    }

    cout << ans << "\n";

    return 0;
}