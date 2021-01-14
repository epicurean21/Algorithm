#include <iostream>
#include <algorithm>

using namespace std;
#define MAX 1000001
int n, arr[MAX], ltor[MAX], rtol[MAX], res1, res2;

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int gcd2(int a, int b) {
    if (b > a)
        swap(a, b);
    while (b != 0) {
        int r = a % b;
        a = b;
        b = r;
    }
    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL), cout.tie(NULL);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    ltor[0] = arr[0];
    for (int i = 1; i < n; i++) {
        ltor[i] = gcd(ltor[i - 1], arr[i]);
    }
    rtol[n - 1] = arr[n - 1];
    for (int i = n - 2; i >= 0; i--) {
        rtol[i] = gcd(rtol[i + 1], arr[i]);
    }
    int t = rtol[1];
    if (arr[0] < t || gcd(arr[0], t) != t) {
        res1 = t;
    }
    for (int i = 1; i < n - 1; i++) {
        t = gcd(ltor[i - 1], rtol[i + 1]);
        if (arr[i] < t || gcd(arr[i], t) != t) {
            if (res1 < t) {
                res1 = t;
                res2 = i;
            }
        }
    }
    if (arr[n - 1] < ltor[n - 2] || gcd(arr[n - 1], ltor[n - 2]) != t) {
        if (res1 < t) {
            res1 = ltor[n - 2];
            res2 = n - 2;
        }
    }
    if (res1 == 0) cout << "-1\n";
    else cout << res1 << " " << arr[res2] << '\n';
    return 0;
}