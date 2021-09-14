/**
 * 2230: 수 고르기 (이분 탐색)
 * 투 포인터로 해결 가능한 문제, 이분탐색으로 시도해봄
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, M, input, ans = INT32_MAX;
vector<int> A;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        cin >> input;
        A.emplace_back(input);
    }

    sort(A.begin(), A.end());
    for (int i = 0; i < N; i++) {
        int m = M + A[i];
        auto iter = upper_bound(A.begin() + i + 1, A.end(), m - 1);
        if (iter == A.end()) continue;
        ans = min(ans, *iter - A[i]);
    }

    cout << ans << '\n';

    return 0;
}