#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define MAX 100001
#define MAX_ANCESTER 20
int N, M, a, b, depth[MAX], par[MAX][MAX_ANCESTER + 1];
bool chk[MAX];
vector<vector<int>> tree;

// 각 노드의 부모와 깊이를 찾아놓자 !
void dfs(int cur, int deep) {
    chk[cur] = true;
    depth[cur] = deep; // 현재 노드의 깊이 저장

    for (int i = 0; i < tree[cur].size(); i++) {
        int next = tree[cur][i];
        if (!chk[next]) {
            par[next][0] = cur; // 자식 노드의 부모 저장
            dfs(next, deep + 1); //
        }
    }
}

void setAncester() {
    for (int i = 1; i < MAX_ANCESTER; i++) {
        for (int j = 1; j <= N; j++) {
            int ancester = par[j][i - 1];
            par[j][i] = par[ancester][i - 1];
        }
    }
}

int LCA(int x, int y) {
    if (depth[x] >= depth[y])
        swap(x, y);

    // y의 깊이를 x까지 맞춰주기
    for (int i = MAX_ANCESTER; i >= 0; i--) {
        if (depth[y] - depth[x] >= (1 << i)) {
            y = par[y][i];
        }
    }

    if (x == y)
        return x;

    for (int i = MAX_ANCESTER; i >= 0; i--) {
        if (par[x][i] != par[y][i]) { // 부모가 다르다면 둘다 깊이 하나씩 올려준다 부모가 같을때까지!
            x = par[x][i];
            y = par[y][i];
        }
    }
    // 이제 x와 y는 같은 부모를 두고있다. 부모를 출력
    return par[x][0];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    tree.resize(N + 1);
    for (int i = 0; i < N - 1; i++) {
        cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    dfs(1, 1); // 루트는 1번노드, 깊이는 1
    setAncester(); // 2^n 조상 구해놓기

    cin >> M;
    for (int i = 0; i < M; i++) {
        cin >> a >> b; // a 와 b의 최소조상을 찾아보자
        cout << LCA(a, b) << '\n';
    }
    return 0;
}