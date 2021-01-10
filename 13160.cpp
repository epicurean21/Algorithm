#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int N, max_num, u, a, b, position;
vector<pair<int, int>> coord;
vector<pair<int, int>> ary;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N;

    for (int i = 0; i < N; i++) {
        cin >> a >> b;
        coord.push_back({a, -1});
        coord.push_back({b, 1});
        ary.push_back({a, b});
    }

    sort(coord.begin(), coord.end());

    for (int i = 0; i < 2 * N; i++) {
        u += coord[i].second;
        if (u < max_num) {
            max_num = u;
            position = coord[i].first;
        }
    }

    cout << -max_num << "\n";
    for (int i = 0; i < N; i++)
        if (ary[i].first <= position && ary[i].second >= position) cout << i + 1 << " ";

    return 0;
}