#include <iostream>
#include <queue>
#include <vector>

using namespace std;
#define MAX 1000003
#define ll long long
int N, M, a, b, cnt;
ll K, ans;
int p[MAX];
priority_queue<pair<ll, pair<int, int>>, vector<pair<ll, pair<int, int>>>, greater<pair<ll, pair<int, int>>>> pq;
vector<bool> con;
vector<ll> dist;

void init() {
    for (int i = 0; i <= N; i++)
        p[i] = i;
    dist.resize(N + 1);
    con.resize(N + 1);
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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> M >> K;
    init();
    for (int i = 1; i <= N; i++) {
        cin >> dist[i];
        p[i] = i;
    }
    for (int i = 0; i < M; i++) {
        cin >> a >> b;
        if (a > b && a != N) // 공사중
            con[b] = true;
        else
            con[a] = true;
    }

    if (M <= 1) {  // 다 한뭉치다? 다리 필요없음
        cout << "YES\n";
        return 0;
    }

    for (int i = 1; i < N; i++)
        if (!con[i])  // 공사중이지 않은애들
            pq.push({0, {i, i + 1}});
    if (!con[N])
        pq.push({0, {N, 1}});
    for (int i = 1; i <= N; i++) {
        pq.push({dist[i], {N + 1, i}});
    }
    while (!pq.empty()) {
        int tmp_a = pq.top().second.first;
        int tmp_b = pq.top().second.second;
        ll tmp_c = pq.top().first;
        pq.pop();
        if (find(tmp_a) != find(tmp_b)) {
            merge(tmp_a, tmp_b);
            cnt++;
            ans += tmp_c;
        }
        if (cnt == N) // Over
            break;
    }

    if (ans <= K && cnt == N)
        cout << "YES\n";
    else
        cout << "NO\n";
    return 0;
}