/**
 * 5676 음주 코딩
 * 세그먼트 트리
 * C: 트리 부분 변경, P: 곱셈 결과 값 출력
 * 굳이 전체 수를 계산하지 않고, -1, 0, 1 로 계산한다.
 */

#include "iostream"
#include "cmath"
#include "vector"

using namespace std;
int n, k, h, x, idx_i, idx_j, v;
char command;
vector<int> segment_tree, input_array;

void print() {
    cout << "\n-----tree print-----\n";
    for (int i = 1; i < segment_tree.size(); i++) {
        cout << segment_tree[i] << " ";
    }
    cout << '\n';
}

int build_segment_tree(int node, int start, int end) {
    if (start == end) return segment_tree[node] = input_array[start];

    int m = (start + end) / 2;
    return segment_tree[node] = build_segment_tree(node * 2, start, m) * build_segment_tree(node * 2 + 1, m + 1, end);
}

int get_value(int node, int start, int end, int left, int right) {
    if (start > right || end < left) return 1;

    if (start >= left && end <= right) return segment_tree[node];
    int m = (start + end) / 2;
    return get_value(node * 2, start, m, left, right) * get_value(node * 2 + 1, m + 1, end, left, right);
}

void update_tree(int node, int start, int end, int idx, int new_value) {
    if (idx < start || end < idx) return;
    if (start == end) {
        segment_tree[node] = input_array[start];
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
        input_array.clear();
        input_array.emplace_back(0);

        for (int i = 1; i <= n; i++) {
            cin >> x;
            x == 0 ? input_array.emplace_back(0) : x < 0 ? input_array.emplace_back(-1) : input_array.emplace_back(1);
        }

        h = (int) ceil(log2(n + 1));
        segment_tree.resize(1 << (h + 1));
        build_segment_tree(1, 1, n);

        for (int i = 0; i < k; i++) {
            cin >> command;
            if (command == 'C') { // 변경
                cin >> idx_i >> v;
                v = v < 0 ? -1 : v == 0 ? 0 : 1;
                input_array[idx_i] = v;
                update_tree(1, 1, n, idx_i, v);
            } else if (command == 'P') { // 곱셈
                cin >> idx_i >> idx_j;
                int calculation = get_value(1, 1, n, idx_i, idx_j);

                if (calculation > 0) answer += '+';
                else if (calculation < 0) answer += '-';
                else answer += '0';
            }
        }
        cout << answer << "\n";
    }

    return 0;
}