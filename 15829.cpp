#include <iostream>
#include <string>

using namespace std;
#define ll long long
#define MOD 1234567891
#define MUL 31

int main() {
    int L;
    cin >> L;
    string s;
    cin >> s;
    ll sum = 0, R = 1;
    for (int i = 0; i < s.length(); i++) {
        sum = (sum + (s[i] - 'a' + 1) * R) % MOD;
        R = (R * MUL) % MOD;
    }
    cout << sum << "\n";
    return 0;
}
