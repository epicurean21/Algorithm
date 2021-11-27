#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int N, input;
vector<int> arr;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    arr.emplace_back(-1);
    for (int i = 0; i < N; i++) {
        cin >> input;
        if (input > arr[arr.size() - 1])
            arr.emplace_back(input);
        else
            arr[lower_bound()
    }

    return 0;
}