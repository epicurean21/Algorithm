/**
 * 1253: 좋다
 * 투 포인터
 */
#include <iostream>
#include <algorithm>

using namespace std;
#define MAX 2002

int N, A[MAX], cnt, tmp;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    for (int i = 0; i < N; i++)
        cin >> A[i];
    sort(A, A + N);

    for (int i = 0; i < N; i++) {
        tmp = A[i];
        int l = 0, r = N - 1, sum = 0;
        while (l < r) {
            sum = A[l] + A[r];
            if (tmp == sum) {
                if (l != i && r != i) {
                    cnt++;
                    break;
                } else if (l == i)
                    l++;
                else if (r == i)
                    r--;
            } else if (tmp > sum) l++;
            else r--;
        }
    }

    cout << cnt << '\n';
    return 0;
}