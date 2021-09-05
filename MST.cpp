/**
 * MST: Minimum Spanning Tree, 최소 신장 트리
 * Greedy한 알고리즘의 일종이다. 즉 모든 정점을 연결하는 그래프 중 최소 cost를 유지하는 것
 * 구현에는 Kruskal Algorithm과 Prim 알고리즘이 존재한다
 * 두 방식 모두 O(M log N)의 수행시간. (HEAP 방식, unsorted Sequence 는 O(N^2))
 * Dense한 그래프라면 M 이 결국 N^2에 수렴한다. 그렇기에 dense graph는 unsorted sequence를 통한 구현이 낫다.
 *
 * Kruskal Algorithm, Union-find를 사용한다.
 * minimum cost로 정렬 (HEAP 이용), cycle을 만들지 않는다면 연결을 추가해준다.
 * 별로 안어려움.
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int getRoot(vector<int> &parent, int x)  // 인수로 넘긴 정점의 부모 정점을 알려줌
{
    if (parent[x] == x) return x;
    return parent[x] = getRoot(parent, parent[x]);
}

void unionParent(vector<int> &parent, int a, int b)  // 두 정점을 병합함. 부모가 같은, 같은 그룹으로.
{
    int par_a = getRoot(parent, a);
    int par_b = getRoot(parent, b);
    if (par_a < par_b) parent[par_b] = par_a;
    else parent[par_a] = par_b;
}

bool find(vector<int> &parent, int a, int b)  // 두 정점이 같은 부모를 가졌는지 확인
{
    int par_a = getRoot(parent, a);
    int par_b = getRoot(parent, b);
    if (par_a == par_b) return true;
    else return false;
}

bool compare(vector<int> a, vector<int> b) {
    return a[2] < b[2];
}

int solution(int n, vector<vector<int>> costs) {
    int answer = 0;

    sort(costs.begin(), costs.end(), compare);

    vector<int> parents(n);

    for (int i = 0; i < parents.size(); i++)
        parents[i] = i;

    for (int i = 0; i < costs.size(); i++) {
        if (!find(parents, costs[i][0], costs[i][1])) {
            unionParent(parents, costs[i][0], costs[i][1]);
            answer += costs[i][2];
        }
    }

    return answer;
}