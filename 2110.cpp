#include <iostream>
#include <algorithm>
#include <vector>
#define MAX 200001
using namespace std;
int N, C, l, r, ans;
vector<int> home(MAX);

bool test(int d) {
    int cnt = C - 1;
    int prev = home[0];
    for (int i = 1; i < N; i++){
        if (home[i] - prev >= d) {
            cnt--;
            if (cnt == 0)
                return true;
            prev = home[i];
        }
    }
    return cnt == 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> C;
    for (int i = 0; i < N; i++) {
        cin >> home[i];
    }
    sort(home.begin(), home.begin() + N);

    l = 1;
    r = home[N - 1];

    while (l <= r) {
        int m = (l + r) / 2;
        if (test(m)) {
            l = m + 1;
        } else
            r = m - 1;
    }

    cout << r << "\n";
    return 0;
}