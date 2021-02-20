#include<iostream>
#include<string>
#include<algorithm>
#include<set>
#include<vector>
#include<math.h>

using namespace std;

vector<pair<int, int>> arr;
vector<vector<int>> dist;
vector<vector<int>> memoization;

int n;
int startInd;
int endInd;

int TSP(int visit, int ind) {
    visit |= (1 << ind);
    if (visit == (1 << n) - 1) { //all visit
        return dist[ind][endInd];
    }

    int& ret = memoization[visit][ind];
    if (ret != -1) return ret;
    ret = 1e9;

    for (int i = 0; i < n; i++) {
        if ((visit & (1 << i)) > 0)  //already visit
            continue;
        ret = min(ret, TSP(visit, i) + dist[ind][i]);
    }
    return ret;
}

int getDist(pair<int, int> a, pair<int, int> b) {
    int d = a.first - b.first;
    if (d < 0) d = -d;
    d += a.second - b.second > 0 ?
         a.second - b.second : b.second - a.second;
    return d;
}

int main() {

    int t = 0;
    cin >> t;
    for (int c = 1; c <= t; c++) {
        cin >> n;

        arr = vector<pair<int, int>>(n + 2);
        startInd = n;
        endInd = n + 1;

        cin >> arr[startInd].first >> arr[startInd].second;
        cin >> arr[endInd].first >> arr[endInd].second;
        for (int i = 0; i < n; i ++) {
            cin >> arr[i].first >> arr[i].second;
        }

        // (index, distance)
        dist = vector<vector<int>>(n+2, vector<int>(n+2, 0));
        memoization = vector<vector<int>>(1 << n, vector<int>(n, -1));

        for (int i = 0; i < n + 2; i++) {
            for (int j = i + 1; j < n + 2; j++) {
                int d = getDist(arr[i], arr[j]);
                dist[i][j] = d;
                dist[j][i] = d;
            }
        }

        int answer = 1e9;
        for (int i = 0; i < n; i++) {
            answer = min(answer, TSP(0, i) + dist[startInd][i]);
        }
        printf("#%d %d\n", c, answer);
    }

    return 0;
}