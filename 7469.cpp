/**
 * 7469 K번째 수 [플레티넘 2]
 * 세그먼트 트리, 머지 소트 트리, 이분 탐색
 * O(n log n + mlog^3n)
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;
#define MAX 100001
int N, M, arr[MAX], I, J, K;
vector<string> tree;

string construct_tree(int node, int start, int end) {
    if (start == end)
        return tree[node] = to_string(arr[start]);

    int m = (start + end) >> 1;
    string left = construct_tree(node * 2, start, m);
    string right = construct_tree(node * 2 + 1, m + 1, end);

    tree[node] = left + right;
    sort(tree[node].begin(), tree[node].end());

    return tree[node];
}

string query(int node, int start, int end, int left, int right) {
    if (start > right || end < left)
        return "";

    if (start >= left && right >= end)
        return tree[node];

    int m = (start + end) >> 1;
    string left_value = query(node * 2, start, m, left, right);
    string right_value = query(node * 2 + 1, m + 1, end, left, right);

    string temp = left_value + right_value;
    sort(temp.begin(), temp.end());

    return temp;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    int h = (int) ceil(log2(N + 1));
    tree.resize(1 << (h + 1));

    for (int i = 1; i <= N; i++)
        cin >> arr[i];

    construct_tree(1, 1, N);
    while (M--) {
        cin >> I >> J >> K;
        string value = query(1, 1, N, I, J);
        cout << value[K - 1] - '0' << '\n';
    }

    return 0;
}