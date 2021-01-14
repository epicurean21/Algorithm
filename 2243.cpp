#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
#define ll long long
#define MAX 1000000
int N, num;
int tree_size;
ll result;

void update(vector<ll> &tree, int node, int start, int end, int idx, ll diff) {
    if (!(start <= idx && idx <= end))
        return;

    tree[node] += diff;

    if (start != end) {
        int mid = (start + end) / 2;
        update(tree, node * 2, start, mid, idx, diff);
        update(tree, node * 2 + 1, mid + 1, end, idx, diff);
    }
}

ll query(vector<ll> &tree, int node, int start, int end, int k) {
    if ((start == end) && !result) {
        cout << start << "\n";
        return start;
    }

    if (result == 0 && (node * 2 <= tree_size && tree[node * 2] >= k))
        return result = query(tree, node * 2, start, (start + end) / 2, k);
    k -= tree[node * 2];

    if (result == 0 && (node * 2 + 1 <= tree_size && tree[node * 2 + 1] >= k))
        return result = query(tree, node * 2 + 1, (start + end) / 2 + 1, end, k);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;
    int height = (int) ceil(log2(MAX));
    tree_size = 1 << (height + 1);
    vector<ll> tree(tree_size);
    for (int i = 0; i < N; i++) {
        cin >> num;
        if (num == 1) {
            int K;
            cin >> K;
            int idx = query(tree, 1, 0, MAX - 1, K);
            result = 0;
            update(tree, 1, 0, MAX - 1, idx, -1);
        } else if (num == 2) {
            int rank;
            ll val;
            cin >> rank >> val;
            update(tree, 1, 0, MAX - 1, rank, val);
        }
    }
    return 0;
}