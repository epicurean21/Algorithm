/**
 * 14438 수열과 쿼리 17
 * 세그먼트 트리
 * 1 i v: Ai를 v로 변경
 * 2 i j: Ai, ... ,Aj 에서 크기가 가장 작은 값 출력
 */

#include <iostream>
#include <cmath>
#include <vector>

using namespace std;
#define ll long long
int N, M, Q, I, J, V;
vector<ll> tree, A;

ll min(ll a, ll b) {
    return a > b ? b : a;
}

ll construct_tree(int node, int start, int end) {
    if (start == end)
        return tree[node] = A[start];
    int m = (start + end) / 2;
    return tree[node] = min(construct_tree(node * 2, start, m), construct_tree(node * 2 + 1, m + 1, end));
}

ll update_tree(int node, int start, int end, int idx) {
    if (start > idx || end < idx)
        return tree[node];
    if (start == end)
        return tree[node] = A[idx];

    int m = (start + end) / 2;

    return tree[node] = min(update_tree(node * 2, start, m, idx), update_tree(node * 2 + 1, m + 1, end, idx));
}

ll get_min_value(int node, int start, int end, int left, int right) {
    if (start > right || end < left) return INT64_MAX;

    if (start >= left && end <= right)
        return tree[node];

    int m = (start + end) / 2;
    return min(get_min_value(node * 2, start, m, left, right), get_min_value(node * 2 + 1, m + 1, end, left, right));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    int h = (int) ceil(log2(N + 1));
    tree.resize(1 << (h + 1));
    A.resize(N + 1);
    for (int i = 1; i <= N; i++)
        cin >> A[i];

    construct_tree(1, 1, N);

    cin >> M;
    while (M--) {
        cin >> Q;
        if (Q == 1) {
            cin >> I >> V;
            A[I] = V;
            update_tree(1, 1, N, I);
        } else if (Q == 2) {
            cin >> I >> J;
            cout << get_min_value(1, 1, N, I, J) << "\n";
        }
    }

    return 0;
}