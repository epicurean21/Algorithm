#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define INF 9999999999
int H, N, u, d, ans = INF, cnt = 1;

vector<int> up;
vector<int> down;

void find() {
    for (int i = 1; i <= H; i++) {
        int tmp = down.size() - (lower_bound(down.begin(), down.end(), i) - down.begin());
        tmp += up.size() - (upper_bound(up.begin(), up.end(), H - i) - up.begin());

        if (tmp == ans)
            cnt++;
        else if (ans > tmp) {
            ans = tmp;
            cnt = 1;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> H;
    for (int i = 0; i < N / 2; i++) {
        cin >> u >> d;
        up.push_back(u);
        down.push_back(d);
    }
    sort(up.begin(), up.end());
    sort(down.begin(), down.end());

    find();
    cout << ans << " " << cnt << "\n";
    return 0;
}