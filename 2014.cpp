#include <iostream>
#include <vector>
#include <queue>

using namespace std;
#define ll long long
int K, N, ans;
ll tmp;
vector<ll> num;
priority_queue<ll, vector<ll>, greater<ll>> pq;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> K >> N;
    for (int i = 0; i < K; i++) {
        cin >> tmp;
        num.push_back(tmp);
        pq.push(tmp);
    }

    for (int i = 0; i < N; i++) {
        ans = pq.top();
        pq.pop();
        for (int j = 0; j < K; j++) {
            tmp = ans * num[j];
            pq.push(tmp);

            if (!(ans % num[j]))
                break;
        }
    }
    cout << ans << "\n";
    return 0;
}