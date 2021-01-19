#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define MAX 100001
#define node 20
// Problem Num. 11438, LCA 2
int N, M, depth[MAX], ancestor[MAX][node + 1]; // 18 이면 0 ~ 17.. 2^17 까지 담갰다는거.
vector<vector<int>> tree(MAX);
bool visited[MAX];

// root = 1

// 부모, 자신, 깊이
// dfs 를 돌면서 부모 자식 관계를 설정한다. 바로 위 부모 관계를 설정해주는것 !
void dfs(int parent, int cur, int param_depth) {
    if (visited[cur])
        return;
    visited[cur] = true;
    depth[cur] = param_depth;
    ancestor[cur][0] = parent;
    for (int i = 0; i < tree[cur].size(); i++) {
        dfs(cur, tree[cur][i], param_depth + 1);
    }
}

// a 와 b의 최소조상을 찾기위한 함수
int lca(int a, int b) {
    // 깊이가 서로 다르면 맞춰준다
    // depth는 a가 b보다 클 수 있다. depth[a] > depth[b]..
    // 이걸 간편하게 !
    // a의 깊이가 b보다 깊게 만들어서 쉽게 처리하기 위해.
    if (depth[a] < depth[b])
        swap(a, b);

    if (depth[a] != depth[b]) { // 깊이가 서로 다르다? a의 깊이가 더 깊을꺼임
        // a의 깊이를 b의 깊이까지 맞춘다. 얼마나?
        int diff = depth[a] - depth[b]; // diff 만큼
        // 예를들어 diff 가 13 (깊이 차이가 13이다?)
        // 우리가 아는건 2^n 조상만 안다.
        // diff = 13 = 8 + 4 + 1
        // a -> 8번째 조상, 4번째 조상, 부모
        for(int i = node; i >= 0; i--) {
            if(diff >= (1 <<i))
                a = ancestor[a][i];;
        }
    }

    if (a == b)
        return a;

    // lca 찾기 !
    for (int i = node; i >= 0; i--) {
        if (ancestor[a][i] != ancestor[b][i]) {
            a = ancestor[a][i];
            b = ancestor[b][i];
        }
    }

    // LCA의 바로 아래까지 왔음. 부모를 출력
    return ancestor[a][0];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    for (int i = 0; i < N - 1; i++) {
        int a, b;
        cin >> a >> b;
        // 트리에 양 방향으로 연결
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    // LCA를 위한 자료 수집: 깊이, 1 / 2 / 4 . . . 조상, dfs()
    // 1번 (Root)의 조상을 1로 하면 편하다. 루트의 조상을 1로하면 편하다. 1의 조상, 2^1 조상, 2^2 조상... 쭉 1이 된다.
    dfs(1, 1, 1);
    // dfs 를 돌면서 부모 자식 관계를 설정한다. 바로 위 부모 관계를 설정해주는것 !

    // 2^1, 2^2, 2^3 .... 조상을 미리 구해놓자 !
    for (int i = 1; i <= node; i++) { // 2^i번째 조상
        for (int j = 1; j <= N; j++) { // 1번노드, 2번노드, 3번노드, ...., N번 노드까지
            int tmp = ancestor[j][i - 1];
            ancestor[j][i] = ancestor[tmp][i - 1]; // 나의 i - 1번째 조상이 i 번째 조상이된다.
            // 예를들어 1 -> 2, 3 -> 4, 5, 6, 7 이라면 4의 조상 2^0 = 2, 2^1 = 1,
            // j가 4일 때
            // tmp 가 2
            // ancestor[4][0]은 2의 부모 ancestor[4][1]은 ancestor[ancestor[2][0]][0]!
        }
    }

    // 처리 할 쿼리들
    cin >> M;
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        cout << lca(a, b) << "\n";
    }
    return 0;
}