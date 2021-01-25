#include <iostream>
#include <vector>
#include <cmath>

using namespace std;
#define MAX 5000001
int N, L, A[MAX];
vector<int> tree;

int min(int a, int b) {
    return a > b ? b : a;
}

// node 번호, node 시작번호, node 끝 번호
int construct_tree(int node, int start, int end) {
    if (start == end)
        return tree[node] = A[start];

    int m = (start + end) / 2;
    return tree[node] = min(construct_tree(node * 2, start, m), construct_tree(node * 2 + 1, m + 1, end));
}

// 특정 범위 left 와 right에서의 최솟값을 구하자
int query(int node, int start, int end, int left, int right) {
    if (start > right || end < left)
        return 9875432198;

    if (start >= left && end <= right)
        return tree[node];

    int m = (start + end) / 2;
    return min(query(node * 2, start, m, left, right), query(node * 2 + 1, m + 1, end, left, right));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> L;
    for (int i = 1; i <= N; i++)
        cin >> A[i];

    // Construct Segment Tree
    int height = (int) ceil(log2(N + 1));
    tree.resize(1 << height + 1);
    construct_tree(1, 1, N);
    for (int i = 1; i <= N; i++) { // Di 계산 i-L+1 ~ i
        int sIdx = i - L + 1;
        int eIdx = i;
        if (sIdx <= 0) sIdx = 1;
        cout << query(1, 1, N, sIdx, eIdx) << " ";
    }
    return 0;
}