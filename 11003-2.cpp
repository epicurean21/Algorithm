#include <iostream>
#include <queue>

using namespace std;

#define MAX 5000001
int N, L, A[MAX];
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> L;
    for (int i = 1; i <= N; i++)
        cin >> A[i];

    for (int i = 1; i <= N; i++) {
        int idx = i - L + 1;
        if (idx <= 0) idx = 1;
        pq.push({A[i], i});
        while (pq.top().second <= idx - 1)
            pq.pop();
        cout << pq.top().first << " ";
    }
    return 0;
}