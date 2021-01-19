#include <iostream>
#include <string>

using namespace std;
#define ll long long

ll solve(int num) {
    ll tmp = 0;
    for (int start = 1, len = 1; start <= num; start *= 10, len++) {
        int end = start * 10 - 1;
        if (end >= num)
            tmp += (long) ((num - start + 1) * len);
        else
            tmp += (long) ((end - start + 1) * len);
    }
    return tmp;
}

int N, K;
ll ans;
string str;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> K;

    if (solve(N) < K)
        cout << "-1\n";
    else {
        int left = 1, right = N;
        while (left <= right) {
            int m = (left + right) / 2;
            ll tmp = solve(m);
            if (tmp < K)
                left = m + 1;
            else {
                ans = m;
                right = m - 1;
            }
        }
        str = to_string(ans);
        ll tmp = solve(ans);
        cout << str[str.size() - (tmp - K) - 1] << "\n";
    }
    return 0;
}