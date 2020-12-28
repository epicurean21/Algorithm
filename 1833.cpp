#include <iostream>
#include <queue>

using namespace std;
#define MAX 202

int N, price, cost, p[MAX], been[MAX][MAX];
priority_queue<pair<int, pair<int,int>>, vector<pair<int, pair<int,int>>>, greater<pair<int, pair<int,int>>>> pq;
queue<pair<int, int>> q;

int find(int x) {
    if (p[x] == x)
        return x;
    return p[x] = find(p[x]);
}

void merge(int a, int b) {
    int aa = find(a);
    int bb = find(b);

    p[aa] = bb;
}

void init() {
    for (int i = 0; i <= N; i++)
        p[i] = i;
}

void mst() {
    while (!pq.empty()) {
        int x = pq.top().second.first;
        int y = pq.top().second.second;
        int c = pq.top().first;
        pq.pop();

        if (find(x) == find(y)) continue;

        merge(x, y);
        cost += c;
        q.push({x, y});
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N;
    init();
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            cin >> price;
            if (i == j) continue;
            if (been[i][j]) continue;
            //if (price == 1000) continue;

            if (price < 0) { // highway exists
                int a = find(i);
                int b = find(j);
                merge(a, b);
                cost += (-1 * price);
                been[i][j] = 1;
                been[j][i] = 1;
            } else {
                pq.push({price, {j, i}});
            }
        }
    }
    mst();
    cout << cost << " " << q.size() << "\n";
    while (!q.empty()) {
        cout << q.front().first << " " << q.front().second << "\n";
        q.pop();
    }
    return 0;
}