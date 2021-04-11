/*
#include <iostream>
#include <vector>
#include <cstring>

using namespace std;
#define MAX 11
#define INF 2001
int N, population[MAX], x, y, chk1, chk2, ans = INF, total;
bool been[MAX];
vector<vector<int>> map(MAX);

int min(int a, int b) {
    return a > b ? b : a;
}

int diff(int a, int b) {
    return abs(a - b);
}

void dfs_check(int cur, int popu) {
    for (int i = 0; i < map[cur].size(); i++) {
        int next = map[cur][i];
        if (been[next]) continue;
        been[next] = true;
        chk2 += population[next];
        dfs_check(next, popu + population[next]);
        been[next] = false;
    }
}

void dfs(int cur, int pop) {
    been[cur] = true;
    for (int i = 0; i < map[cur].size(); i++) {
        int next = map[cur][i];
        if (been[next]) continue;
        been[next] = true;
        chk2 = population[next];
        chk1 = pop;
        dfs_check(next, population[next]);
        if (total - chk2 == chk1) { // 모든 구역 커버 가능.
            ans = min(ans, diff(chk1, chk2));
        }
        been[next] = false;
        chk1 += population[next];
        dfs(next, pop + population[next]);
        chk1 -= population[next];
        been[next] = false;
    }
}

void cnt_place1(int cur) {
    been[cur] = true;
    chk1 += population[cur];
    for (int i = 0; i < map[cur].size(); i++) {
        int next = map[cur][i];
        if (!been[next])
            cnt_place1(next);
    }
}

void cnt_place2(int cur) {
    been[cur] = true;
    chk2 += population[cur];
    for (int i = 0; i < map[cur].size(); i++) {
        int next = map[cur][i];
        if (!been[next])
            cnt_place2(next);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> population[i];
        total += population[i];
    }
    for (int i = 1; i <= N; i++) {
        cin >> x;
        for (int j = 0; j < x; j++) {
            cin >> y;
            map[i].push_back(y);
        }
    }

    int cnt = 0;
    for (int i = 1; i <= N; i++) {
        if (!been[i]) {
            cnt++;
            if (chk1)
                cnt_place2(i);
            else
                cnt_place1(i);
        }
    }

    if (cnt > 2) {
        cout << "-1\n";
        return 0;
    } else if (cnt == 2) {
        cout << abs(chk1 - chk2) << '\n';
        return 0;
    }

    for (int i = 1; i <= N; i++) { // 구역 한개 씩 돌려보자
        memset(been, false, sizeof(been));
        dfs(i, population[i]);
    }

    if (ans == INF)
        cout << "-1\n";
    else
        cout << ans << "\n";
    return 0;
}
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include<cmath>
#include<cstring>

using namespace std;
#define MAX 11
#define INF 2001
int N, population[MAX], ans = INF, x, y;
int places[MAX];
bool been[MAX];
int score[2];
vector<vector<int>> map(MAX);

void dfs(int cur, int team) {
    been[cur] = true;
    score[team] += population[cur];
    for (int i = 0; i < map[cur].size(); i++) {
        int nxt = map[cur][i];
        if (team != places[nxt - 1])
            continue;
        if (been[nxt])
            continue;
        dfs(nxt, team);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> population[i];
    }
    for (int i = 1; i <= N; i++) {
        cin >> x;
        for (int j = 0; j < x; j++) {
            cin >> y;
            map[i].push_back(y);
        }
    }

    for (int i = 1; i <= N / 2; i++) {
        memset(places, 0, sizeof(places));
        for (int j = 0; j < i; j++) {
            places[j] = 1;
        }
        reverse(places, places + N);
        do {
            int cnt = 0;
            score[0] = score[1] = 0;
            memset(been, false, sizeof(been));
            for (int i = 1; i <= N; i++) {
                if (been[i])
                    continue;
                dfs(i, places[i-1]);
                cnt++;
            }
            if (cnt != 2)
                continue;
            ans = min(ans, abs(score[0] - score[1]));
        } while (next_permutation(places, places + N));
    }
    if (ans == INF)
        cout << "-1\n";
    else
        cout << ans << '\n';
    return 0;
}