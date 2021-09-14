/**
 * 2230: 수 고르기
 * 수열 A에서 두 수를 골랐을 때 차이가 M 이상이면서 제일 작은 차이를 출력
 * M은 20억, 수열 A는 최대 20만개..
 * 그냥 단순 찾기로 2중 for문? 등을 돌리면 무조건 시간초과
 * 투 포인터로 O(N) 만에 찾아야 한다.
 * 일단 정렬을 시켜야겠지 ~?
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
    int l = 0, r = 0;
    while (l <= r && (r <= N - 1 && l >= 0)) {
        if (A[r] - A[l] >= M) {
            ans = min(ans, A[r] - A[l]);
            l++;
        } else {
            r++;
        }
    }

    cout << ans << '\n';

    return 0;
}