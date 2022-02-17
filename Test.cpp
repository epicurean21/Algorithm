#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
#define ll unsigned long long
ll M, N, demand_left;
vector<ll> demand;
ll fury, cal;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> M >> N;
    demand.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> demand[i];
        demand_left += demand[i];
    }

    sort(demand.begin(), demand.end());
    demand_left -= M;
    for (int i = 0; i < N; i++) {
        cal = min(demand[i], demand_left / (N - i));
        fury += cal * cal;
        demand_left -= cal;
    }
    cout << fury;

    return 0;
}