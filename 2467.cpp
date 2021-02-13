#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;
int N, one = 2100000000;
vector<int> yong;
pair<int, int> ans;

int findDif(int a, int b) {
    return (abs(a) > abs(b)) ? b : a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    for (int i = 0; i < N; i++) {
        int tmp;
        cin >> tmp;
        yong.push_back(tmp);
    }
    sort(yong.begin(), yong.end());
    int l = 0, r = yong.size() - 1;
    while (l < r) {
        int tmp = yong[l] + yong[r];
        if (findDif(tmp, one) == tmp) {
            one = tmp;
            ans = {yong[l], yong[r]};
            if (tmp < 0)
                l++;
            else
                r--;
        } else {
            if (tmp < 0)
                l++;
            else
                r--;
        }
    }
    cout << ans.first << " " << ans.second << '\n';
    return 0;
}