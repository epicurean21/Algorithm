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