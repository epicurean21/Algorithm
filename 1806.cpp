#include <iostream>

using namespace std;
#define MAX 100001
#define INF 987654321
int N, S, A[MAX], sum, length = INF, l, r;

int min(int a, int b) {
    return a < b ? a : b;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> S;
    for (int i = 0; i < N; i++)
        cin >> A[i];

    while (l <= r) {
        if (sum >= S) {
            length = min(length, r - l);
            sum -= A[l++];
        } else if (sum < S)
            sum += A[r++];
        if (sum >= S)
            length = min(length, r - l);
        if (r > N) break;
    }
    if (length != INF)
        cout << length << "\n";
    else
        cout << 0 << "\n";
    return 0;
}