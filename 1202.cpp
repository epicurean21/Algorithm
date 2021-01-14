#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
using namespace std;
#define INF 1000001
#define ll long long
int N, K, M, V, C, idx;
ll ans;
priority_queue<int> pq;
vector<int> backpack;
vector<pair<int,int>> tmp; // 무게, 가치

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> N >> K;
    for (int i = 0; i < N; i++) {
        cin >> M >> V;
        tmp.push_back({M, V}); // min-heap {value, weight}
    }
    for (int i = 0; i < K; i++) {
        cin >> C;
        backpack.push_back(C);
    }
    sort(tmp.begin(), tmp.end());
    sort(backpack.begin(), backpack.end());
    for(int i = 0; i < K; i++) {
        while(idx < N && tmp[idx].first <= backpack[i])
            pq.push(tmp[idx++].second);
        if(!pq.empty()) {
            ans += pq.top();
            pq.pop();
        }
    }

    cout << ans << "\n";
    return 0;
}