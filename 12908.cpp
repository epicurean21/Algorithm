#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;
#define INF 999999999999
#define ll long long
int xs, ys, xe, ye, x_1, y_1, x_2, y_2;
ll ans = INF;
vector<pair<pair<int, int>, pair<int, int>>> teleport;
vector<int> been;

ll dist(int a, int b, int c, int d) {
    return abs(c - a) + abs(d - b);
}

void cal() {
    do {
        ll cnt = 0;
        int nx = xs;
        int ny = ys;
        for (int i = 0; i < been.size(); i++) {
            cnt += dist(nx, ny, teleport[been[i]].first.first, teleport[been[i]].first.second);
            if (teleport[been[i]].second.first == xe && teleport[been[i]].second.second == ye)
                break;
            cnt += 10;
            nx = teleport[been[i]].second.first;
            ny = teleport[been[i]].second.second;
        }
        ans = min(ans, cnt);
    } while(next_permutation(been.begin(), been.end()));

}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> xs >> ys >> xe >> ye;
    for (int i = 0; i < 3; i++) {
        cin >> x_1 >> y_1 >> x_2 >> y_2;
        teleport.push_back({{x_1, y_1},
                            {x_2, y_2}});
        teleport.push_back({{x_2, y_2},
                            {x_1, y_1}});
    }
    teleport.push_back({{xe, ye},
                        {xe, ye}});
    for(int i = 0; i < 7; i++)
        been.push_back(i);

    cal();

    cout << ans << "\n";
    return 0;
}