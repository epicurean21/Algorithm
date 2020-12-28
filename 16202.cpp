#include <iostream>
#include <queue>

using namespace std;
#define MAX 1001
priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;
priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq_tmp;
int N, M, K, a, b, cost, cnt;
int p[MAX];

void init() {
    for (int i = 0; i <= N; i++)
        p[i] = i;
    cost = 0;
    cnt = 0;
    while(!pq_tmp.empty()) {
        pq.push(pq_tmp.top());
        pq_tmp.pop();
    }
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

    for (int i = 1; i <= M; i++) {
        cin >> a >> b;
        pq.push({i, {a, b}});
    }

    while (K--) {
        init();
        while (!pq.empty()) {
            int a = pq.top().second.first;
            int b = pq.top().second.second;
            int c = pq.top().first;
            pq_tmp.push(pq.top());
            pq.pop();
            if(find(a) == find(b)) continue;
            merge(a, b);
            cost += c;
            cnt++;
        }

        if(cnt == N - 1) {
            pq_tmp.pop();
            cout << cost << " ";
        }
        else
            cout << "0 ";
    }
    cout << "\n";

    return 0;
}