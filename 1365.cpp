#include <iostream>
#include <vector>

using namespace std;
#define MAX 100001
int N, input, lcs[MAX], len = -1;
vector<int> arr;

void lower_bound(int n) {
    int tmp = arr[n];

    for (int i = 0; i <= len; i++) {
        if (tmp < lcs[i]) {
            lcs[i] = tmp;
            break;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;

    for (int i = 0; i < N; i++) {
        cin >> input;
        arr.emplace_back(input);
    }

    for (int i = 0; i < arr.size(); i++) {
        if (len == -1)
            lcs[++len] = arr[i];
        else if (lcs[len] <= arr[i])
            lcs[++len] = arr[i];
        else if (lcs[len] > arr[i])
            lower_bound(i);
    }

    cout << N - (len + 1) << '\n';

    return 0;
}