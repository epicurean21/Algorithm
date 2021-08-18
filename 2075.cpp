#include <iostream>
#include <queue>

using namespace std;
int N, tmp;
priority_queue<int, vector<int>, greater<>> pq;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    for (int i = 0; i < N * N; i++) {
        cin >> tmp;
        if (pq.size() < N) {
            pq.push(tmp);
        } else if (pq.size() == N) {
            if (pq.top() < tmp) {
                pq.pop();
                pq.push(tmp);
            }
        }
    }
    cout << pq.top();
    return 0;
}