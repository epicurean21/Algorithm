#include <iostream>

using namespace std;
#define MAX 1000001
#define ll long long
int N, A[MAX], B, C;
ll cnt;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    for (int i = 0; i < N; i++)
        cin >> A[i];
    cin >> B >> C;
    for (int i = 0; i < N; i++) {
        A[i] -= B;
        cnt++;
        if (A[i] > 0) {
            cnt += (A[i] / C);
            A[i] %= C;
        }
        if (A[i] > 0)
            cnt++;
    }
    cout << cnt << '\n';
    return 0;
}