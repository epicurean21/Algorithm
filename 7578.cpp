#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;
#define ll long long
#define MAX 1000010
// Segment Tree
int N, tmp;
vector<ll> tree;
vector<ll> map;
int idx[MAX];
void update(int node, int idx, int start, int end)
{
    if (idx < start || end < idx)
        return;

    if (start == end)
    {
        tree[node] = 1;
        return;
    }

    int m = (start + end) / 2;
    update(node * 2, idx, start, m);
    update(node * 2 + 1, idx, m + 1, end);

    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

ll query(int node, int start, int end, int left, int right)
{
    if (right < start || left > end)
        return 0;

    if (start >= left && end <= right)
        return tree[node];

    int m = (start + end) / 2;
    return query(node * 2, start, m, left, right) + query(node * 2 + 1, m + 1, end, left, right);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    int height = (int) ceil(log2(N + 1));
    tree.resize(1 << (height + 1));
    map.resize(N + 1);
    for (int i = 1; i <= N; i++)
        cin >> map[i];

    for (int i = 1; i <= N; i++) {// index를 저장
        cin >> tmp;
        idx[tmp] = i;
    }

    ll ans = 0;
    for(int i = 1; i <= N; i++) {
        ans += query(1, 1, N, idx[map[i]], N);
        update(1, idx[map[i]], 1, N);
    }
    cout << ans << '\n';
    return 0;
}