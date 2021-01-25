#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;
#define INF 987654321
int N, M, dist[15][102];
vector<int> ans, combi;
vector<pair<int, int>> home, chicken;

int getDist(int x, int y, int a, int b) {
    return abs(x - a) + abs(y - b);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    for (int i = 1; i <= N; i++) { // r
        for (int j = 1; j <= N; j++) { // c
            int a;
            cin >> a;
            if (a == 1)
                home.push_back({j, i});
            else if (a == 2)
                chicken.push_back({j, i});
        }
    }

    for (int i = 0; i < chicken.size(); i++) {
        int chickenX = chicken[i].first;
        int chickenY = chicken[i].second;
        int tmp = 0;
        for (int j = 0; j < home.size(); j++) {
            int homeX = home[j].first;
            int homeY = home[j].second;
            int distance = getDist(chickenX, chickenY, homeX, homeY);
            tmp += distance;
            dist[i][j] = distance;
        }
    }

    for (int i = 0; i < M; i++)
        combi.push_back(1);
    for (int i = 0; i < chicken.size() - M; i++)
        combi.push_back(0);

    sort(combi.begin(), combi.end());

    do {
        int tmp[123];
        for(int i = 0; i < home.size(); i++)
            tmp[i] = INF;
        for (int i = 0; i < combi.size(); i++) { // combi는 집 개수
            if (combi[i] == 1) { // i 가 idx
                for (int j = 0; j < home.size(); j++)
                    if (dist[i][j])
                        tmp[j] = min(tmp[j], dist[i][j]);
            }
        }
        int cal = 0;
        for (int i = 0; i < home.size(); i++)
            if (tmp[i] != INF)
                cal += tmp[i];
        ans.push_back(cal);
    } while (next_permutation(combi.begin(), combi.end()));

    sort(ans.begin(), ans.end());
    cout << ans[0] << '\n';

    return 0;
}