#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>

using namespace std;
#define MAX 10001
int N, M, t, a, b, c, ans;
int p[MAX];
priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;
priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> tmp_pq;

void init() {
    for (int i = 0; i <= N; i++)
        p[i] = i;
}

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

void mst() {
    while (!pq.empty()) {
        int tmp_a = pq.top().second.first;
        int tmp_b = pq.top().second.second;
        int tmp_c = pq.top().first;
        pq.pop();

        int aa = find(tmp_a);
        int bb = find(tmp_b);

        if (aa == bb) continue;
        merge(aa, bb);
        ans += tmp_c;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> M >> t;
    init();
    for (int i = 0; i < M; i++) {
        cin >> a >> b >> c;
        pq.push({c, {a, b}});
    }

    mst();
    ans += (N - 1) * (N - 2) / 2 * t;
    cout << ans << "\n";
    return 0;
}