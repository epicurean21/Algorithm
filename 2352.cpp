#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define ll long long
#define INF 1987654321
int N, maximum, big, small = INF;

int min(int a, int b) {
    return a > b ? b : a;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    vector<int> money(N + 1);
    for (int i = 0; i < N; i++) {
        cin >> money[i];
        small = min(money[i], small);
        big = max(big, money[i]);
    }
    cin >> maximum;
    sort(money.begin(), money.end());

    ll ans = maximum / N;
    while (small <= big) {
        ll m = (big + small) / 2;
        ll tmp = 0;
        for (int i = 1; i <= N; i++) {
            if (money[i] > m)
                tmp += m;
            else
                tmp += money[i];
        }
        if (tmp > maximum) {
            big = m - 1;
        } else {
            small = m + 1;
            ans = m;
        }
    }
    cout << ans << '\n';
    return 0;
}