/**
 * 2776 암기 왕
 * set, map
 */
#include "iostream"
#include "unordered_set"

using namespace std;

int t, n, m, input;
unordered_set<int> note;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> t;
    while (t--) {
        note.clear();
        cin >> n;
        while (n--) {
            cin >> input;
            note.emplace(input);
        }
        cin >> m;
        while (m--) {
            cin >> input;
            if (note.count(input)) cout << 1 << '\n';
            else cout << 0 << '\n';
        }
    }
    return 0;
}