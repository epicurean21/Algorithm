#include <iostream>
#include <string>

using namespace std;
string n;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    while (cin >> n) {
        if (n == "0") break;
        int l = 0, r = n.length() - 1;
        bool ans = true;
        while (l < r) {
            if (n[l] != n[r]) ans = false;
            l++;
            r--;
        }
        if (ans) cout << "yes\n";
        else cout << "no\n";
    }
    return 0;
}