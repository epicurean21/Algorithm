#include <iostream>
#include <vector>

using namespace std;

// 단절점 !

int v, e, cnt, visit_order[10010], num = 1; // 방문순서를 저장하기위한 visit_order 변수와 순서를 저장한 num 변수
bool ans[10010]; // 단절점이면 true로 체크
vector<int> adj[10010];

/*
* dfs를 이용해 방문 순서를 저장해놓자 !
* 예외: 루트일 경우 -> 자식 수가 2개 이상이면 단절점이다.
* 루트가 아닐경우 -> 나의 방문순서와 자식들이 만나는 방문순서 중 가장 작은 값을 비교
 */
int dfs(int cur, bool isRoot) {
//    if (visit_order[cur] != 0) 필요없다 어짜피 들어가기전에 확인함
//        return 0;
    visit_order[cur] = num++; // 나 (=cur)의 번호
    int min_visit_order = visit_order[cur]; // 내 자식들이 만날수 있는 점중에서 가장 작은점.
    int childCnt = 0;

    for (int i = 0; i < adj[cur].size(); i++) {
        int next = adj[cur][i];
        if (visit_order[next]) {
/*          혹시 이미 방문을 했냐? min_visit_order와 비교를 해볼수있다.
            이 방법을 이용해야
             " A번 정점에서 자식 노드들이 정점 A를 거치지 않고
             정점 A보다 빠른 방문번호를 가진 정점으로 갈 수 없다면 단절점이다. " 를 찾을 수 있다.
*/
            min_visit_order = min(min_visit_order, visit_order[next]);
        } else { // 새롭게 방문하는 경우 !
            int tmp = dfs(next, false);
            min_visit_order = min(tmp, min_visit_order);
            childCnt++; // 자식수도 증가 !

            if (!isRoot && tmp >= visit_order[cur]) {
                // 루트가 아니면서 자식 노드들이 해당 정점보다 빠른 방문번호를 가진 정점으로 갈 수 없다면 단절점
                ans[cur] = true;
            }
        }
    }
    if (isRoot) {
        // 루트이고, 자식이 두개 이상이면 단절점
        if (childCnt >= 2)
            ans[cur] = true;
    }
    return min(min_visit_order, visit_order[cur]); // 내가 (=cur) 만난 점중에서 방문순서가 가장 낮은점을 반환함..
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> v >> e;
    for (int i = 0; i < e; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    // 단절점을 찾고
    for (int i = 1; i <= v; i++) {
        if (visit_order[i] == 0)
            dfs(i, true);
    }

    // 출력
    // 개수
    for (int i = 1; i <= v; i++)
        if(ans[i])
            cnt++;
    cout << cnt << "\n";
    for (int i = 1; i <= v; i++) {
        if (ans[i])
            cout << i << " ";
    }
    return 0;
}