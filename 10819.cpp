/**
 * 10819 차이를 최대로
 * 백트래킹, 조합, Next Permutation
 */
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
int N, ans;
vector<int> A;

int calculate_and_abs(int a, int b) {
    return a - b < 0 ? -(a - b) : a - b;
}

int calculate_equation() {
    int value = 0;
    for (int i = 0; i < N - 1; i++)
        value += calculate_and_abs(A[i], A[i + 1]);
    return value;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> N;
    A.resize(N);
    for (int i = 0; i < N; i++)
        cin >> A[i];
    sort(A.begin(), A.end());

    do {
        ans = max(calculate_equation(), ans);
    } while (next_permutation(A.begin(), A.end()));

    cout << ans << '\n';

    return 0;
}