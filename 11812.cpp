#include <iostream>
#include <algorithm>

using namespace std;
#define ll long long
ll N;
int K, Q;

ll parent(ll n, int k) {
    return (n + k - 2) / k;
}

int LCA(ll n1, ll n2) {
    int diff = 0;
    while (n1 != n2) {
        while (n1 > n2) {
            diff++;
            n1 = parent(n1, K);
        }
        while (n2 > n1) {
            diff++;
            n2 = parent(n2, K);
        }
    }
    return diff;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> K >> Q;
    while (Q--) {
        ll n1, n2;
        cin >> n1 >> n2;
        if (K == 1) {
            cout << abs(n1 - n2) << '\n';
            continue;
        }
        cout << LCA(n1, n2) << '\n';
    }
    return 0;
}