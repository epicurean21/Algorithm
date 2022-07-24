/**
 * 25192 인사성 밝은 곰곰이
 * set
 */
#include <iostream>
#include <unordered_set>

using namespace std;

int N, ans;
string message;
unordered_set<string> names;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> N;
    while (N--) {
        cin >> message;
        if (message == "ENTER") {
            ans += names.size();
            names = unordered_set<string>();
        } else
            names.insert(message);
    }
    ans += names.size();

    cout << ans << '\n';
    return 0;
}