#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;
#define ll long long
int N;
ll M, cnt, x;
vector<pair<ll, ll>> H;
vector<ll> tree;

bool possible(ll height) {
    ll len = 0;
    for (int i = 0; i < N; i++)
        if (tree[i] - height > 0) //
            len += tree[i] - height;

    if (len >= M)
        return true;

    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        cin >> x;
        tree.push_back(x);
    }
    sort(tree.begin(), tree.end());
    ll tallest = tree[N - 1];
    ll shortest = tallest - M;
    while (shortest <= tallest) {
        ll height = (shortest + tallest) / 2;
        if (possible(height)) {
            cnt = max(cnt, height);
            shortest = height + 1;
        } else
            tallest = height - 1;
    }
    cout << cnt << '\n';
    return 0;
}