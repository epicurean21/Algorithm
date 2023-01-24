#include <iostream>
#include <vector>

using namespace std;

vector<int> merge_sort(vector<int> input) {
    if (input.empty() || input.size() == 1) {
        return input;
    }

    int m = (int) input.size() / 2;
    vector<int> left_half, right_half;
    for (int i = 0; i < m; i++) {
        left_half.emplace_back(input[i]);
    }
    for (int i = m; i < input.size(); i++) {
        right_half.emplace_back(input[i]);
    }

    left_half = merge_sort(left_half);
    right_half = merge_sort(right_half);

    input.clear();
    int left_i = 0, right_i = 0;
    while (left_i != left_half.size() || right_i != right_half.size()) {
        if (left_i == left_half.size()) {
            if (right_i != right_half.size()) {
                input.emplace_back(right_half[right_i++]);
                continue;
            }
        }

        if (right_i == right_half.size()) {
            if (left_i != left_half.size()) {
                input.emplace_back(left_half[left_i++]);
                continue;
            }
        }

        if (left_half[left_i] <= right_half[right_i]) {
            input.emplace_back(left_half[left_i++]);
        } else {
            input.emplace_back(right_half[right_i++]);
        }
    }

    return input;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    int n;
    vector<int> input;

    while (cin >> n) {
        if (n == -1) break;

        input.emplace_back(n);
    }

    input = merge_sort(input);

    for (int i: input) {
        cout << i << " ";
    }
    cout << '\n';

    return 0;
}