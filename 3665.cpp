#include <iostream>

using namespace std;
int T, n, m, a, b;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> T;
    while (T--) {
        cin >> n;
        vector<int> rank(n + 1);
        for (int i = 0; i < n; i++)
            cin >> rank[i];
        cin >> m;
        for (int i = 0; i < m; i++) {
            cin >> a >> b;
        }
    }
    return 0;
}