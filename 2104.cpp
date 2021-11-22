#include <iostream>

using namespace std;
#define ll long long
#define MAX 100001
int n, arr[MAX];

ll DnC(int s, int e) {
    int l, r, height;
    ll base;
    if (s == e)
        return (ll) arr[s] * arr[s];
    int mid = (s + e) / 2;
    ll m = max(DnC(s, mid), DnC(mid + 1, e));
    l = mid;
    r = mid + 1;
    base = arr[l] + arr[r];
    height = min(arr[l], arr[r]);
    m = max(m, base * height);

    while (!(l == s && r == e)) {
        if (r < e && (l == s || arr[l - 1] < arr[r + 1])) {
            base += arr[++r];
            height = min(height, arr[r]);
        } else {
            base += arr[--l];
            height = min(height, arr[l]);
        }
        m = max(m, base * height);
    }
    return m;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    cout << DnC(0, n - 1) << '\n';
    return 0;
}