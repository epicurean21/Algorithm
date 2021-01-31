#include <iostream>
#include <vector>

using namespace std;
#define MAX 100001
#define INF 987654321
int N, A, B, C, K, D, E, r;
vector<vector<pair<int, int>>> map;
int depth[MAX];
pair<int, int> p[MAX][22];
pair<int, int> mm[MAX][22];
bool chk[MAX];
int pS = INF, pL = 0;

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a > b ? b : a;
}

void LCA(int a, int b) {
    if (depth[a] > depth[b])
        swap(a, b);

    for (int i = 21; i >= 0; i--) {
        if (depth[b] - depth[a] >= (1 << i)) {
            pS = min(mm[b][i].first, pS);
            pL = max(mm[b][i].second, pL);
            b = p[b][i].first;
        }
    }

    if (a == b)
        return;

    for (int i = 21; i >= 0; i--) {
        if (p[a][i].first != p[b][i].first) {
            int tmp1 = mm[a][i].first;
            int tmp2 = mm[b][i].first;
            pS = min(min(tmp1, tmp2), pS);
            tmp1 = mm[a][i].second;
            tmp2 = mm[b][i].second;
            pL = max(max(tmp1, tmp2), pL);
            a = p[a][i].first;
            b = p[b][i].first;
        }
    }
    pS = min(min(mm[a][0].first, mm[b][0].first), pS);
    pL = max(max(mm[a][0].second, mm[b][0].second), pL);
    return;
}

void dfs(int cur, int d) { // 부모와 깊이를 저장하자
    chk[cur] = true;
    depth[cur] = d;
    for (int i = 0; i < map[cur].size(); i++) {
        int next = map[cur][i].first;
        if (!chk[next]) {
            p[next][0].first = cur;
            //p[next][0].second = map[cur][i].second;
            mm[next][0].first = map[cur][i].second;
            mm[next][0].second = map[cur][i].second;
            dfs(next, d + 1);
        }
    }
}

void f() {
    for (int i = 1; i < 21; i++) {
        for (int j = 1; j <= N; j++) {
            int tmp = p[j][i - 1].first;
            p[j][i].first = p[tmp][i - 1].first;
            mm[j][i].first = min(mm[j][i - 1].first, mm[tmp][i - 1].first);
            mm[j][i].second = max(mm[j][i - 1].second, mm[tmp][i - 1].second);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    /*
    D, E 를 연결하는 경로 중 가장 짧은 도로와 가장 긴 도로의 길이를 출력하기.
    TREE를 만들어서 LCA를 찾아 올라가며 경로를 최신화 하자
    */
    cin >> N;
    map.resize(N + 1);
    for (int i = 0; i < N - 1; i++) {
        cin >> A >> B >> C;
        map[A].push_back({B, C});
        map[B].push_back({A, C});
        r = A;
    }
    dfs(r, 1);
    f();

    cin >> K;
    for (int j = 0; j < K; j++) {
        cin >> D >> E;
        pS = INF;
        pL = 0;
        LCA(D, E);
        cout << pS << " " << pL << '\n';
    }
    return 0;
}