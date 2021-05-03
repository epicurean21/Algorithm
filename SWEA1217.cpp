#include <iostream>

using namespace std;
int N, M, TC;

int solve(int a, int b) {
    int tmp =a;
    for (int i = 1; i < b; i++)
        tmp *= a;
    return tmp;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    for (int tc = 1; tc <= 10; tc++) {

        cin >> TC >> N >> M;

        cout << "#" << tc << " " << solve(N, M) << "\n";
    }
    return 0;
}