#include <iostream>

using namespace std;
#define MAX 10001
int N, M, A[MAX], cnt;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> M;
    for (int i = 0; i < N; i++)
        cin >> A[i];

    //two pointer algorithm
    int left = 0, right = 0;
    while (left <= right && right < N) {
        int sum = 0;
        for (int i = left; i <= right; i++)
            sum += A[i];

        if (sum == M) {
            cnt++;
            right++;
        } else if (sum > M) {
            if (left == right) {
                left++;
                right++;
            } else
                left++;
        } else {
            right++;
        }
    }

    // better way to solve
    int sum = 0, ans = 0;
    left = 0; right = 0;
    while (1) {
        if (sum >= M)
            sum -= A[left++];
        else if (right == N)
            break;
        else
            sum += A[right++];
        if (sum == M)
            ans++;
    }
    cout << cnt << "\n";
    cout << ans << "\n";
    return 0;
}