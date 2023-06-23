/**
 * 5676 음주 코딩
 * 세그먼트 트리
 */

#include "iostream"
#include "cmath"
#include "vector"

#define ll long long
using namespace std;
int n, k, h, idx_i, idx_j, v;
char command;
vector<ll> segment_tree, input_array;

void print() {
    cout << "\n-----tree print-----\n";
    for (int i = 1; i < segment_tree.size(); i++) {
        cout << segment_tree[i] << " ";
    }
    cout << '\n';
}

ll build_segment_tree(int node, int start, int end) {
    if (start == end) return segment_tree[node] = input_array[start];

    int m = (start + end) / 2;
    return segment_tree[node] = build_segment_tree(node * 2, start, m) * build_segment_tree(node * 2 + 1, m + 1, end);
}

ll get_value(int node, int start, int end, int left, int right) {
    if (start > right || end < left) return 1;

    if (start >= left && end <= right) return segment_tree[node];

    int m = (start + end) / 2;
    return get_value(node * 2, start, m, left, right) * get_value(node * 2 + 1, m + 1, end, left, right);
}

void update_tree(int node, int start, int end, int idx, int new_value) {
    if (idx < start || end < idx) return;
    if (start == end) {
        segment_tree[node] = new_value;
        return;
    }

    int m = (start + end) / 2;
    update_tree(node * 2, start, m, idx, new_value);
    update_tree(node * 2 + 1, m + 1, end, idx, new_value);
    segment_tree[node] = segment_tree[node * 2] * segment_tree[node * 2 + 1];
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    while (cin >> n >> k) {
        string answer;
        input_array.resize(n + 1);

        for (int i = 1; i <= n; i++) cin >> input_array[i];

        h = (int) ceil(log2(n + 1));
        segment_tree.resize(1 << (h + 1));
        build_segment_tree(1, 1, n);
        for (int i = 0; i < k; i++) {
            cin >> command;
            if (command == 'C') { // 변경
                cin >> idx_i >> v;
                input_array[idx_i] = v;
                update_tree(1, 1, n, idx_i, v);
            } else if (command == 'P') { // 곱셈
                cin >> idx_i >> idx_j;
                ll calculation = get_value(1, 1, n, idx_i, idx_j);
                //cout << calculation << "\n";
                if (calculation > 0) answer += '+';
                else if (calculation == 0) answer += '0';
                else answer += '-';
            }
        }
        cout << answer << "\n";
    }

    return 0;
}