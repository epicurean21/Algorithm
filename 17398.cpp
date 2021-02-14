#include <iostream>
#include <stack>

using namespace std;
#define MAX 100001
#define ll long long
int N, M, Q, X, Y, A;
int parent[MAX];
ll sz[MAX];
pair<pair<int, int>, bool> edge[MAX];
stack<int> process;
ll ans;

void init() {
    for (int i = 1; i <= M; i++) {
        parent[i] = i;
        sz[i] = 1;
    }
}

int find(int a) {
    if (parent[a] == a)
        return parent[a];
    return parent[a] = find(parent[a]);
}

void merge(int a, int b) {
    int aa = find(a);
    int bb = find(b);

    if (aa == bb) return;

    if (sz[aa] > sz[bb]) { // aa 가 더 큰 집합
        parent[bb] = aa;
        sz[aa] += sz[bb]; // aa집합에 크기를 더해주고
        sz[bb] = 1; // bb 집합의 크기는 이제 1
    } else {
        parent[aa] = bb;
        sz[bb] += sz[aa];
        sz[aa] = 1;
    }
    return;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M >> Q;
    init();
    for (int i = 1; i <= M; i++) {
        cin >> X >> Y;
        edge[i] = {{X, Y}, true};
    }
    for (int i = 0; i < Q; i++) {
        cin >> A;
        edge[A].second = false; // 사용 안되는걸로 변경
        process.push(A); // 자를 (합칠) 간선들을 stack에 넣어서 역순으로 계산하기 위해
    }
    for (int i = 1; i <= M; i++) {
        if (edge[i].second == false) continue;
        int a = edge[i].first.first;
        int b = edge[i].first.second;
        merge(a, b);
    }
    while (!process.empty()) { // 스택을 이용해
        int step = process.top(); // 맨 마지막 단계
        int pa = find(edge[step].first.first);
        int pb = find(edge[step].first.second);
        process.pop();
        if (pa != pb)  // 서로 다른 집합 관계다
            ans += (sz[pa] * sz[pb]);
        merge(pa, pb);
    }
    cout << ans << '\n';
    return 0;
}
/*
6 6 3
1 2
2 3
3 1
3 4
4 5
4 6
4
1
2
답은: 11

6 6 1
1 2
2 3
3 1
3 4
4 5
4 6
4
*/

/*
#include <iostream>
#include <algorithm>
using namespace std;

int N, M, Q, P[100001], disconnect[100001];

bool check[100001];
pair<int, int> graph[100001];

int find(int n)
{
    if (P[n] < 0) return n;
    return P[n] = find(P[n]);
}

void merge(int a, int b)
{
    a = find(a);
    b = find(b);

    if (a == b) return;

    P[a] += P[b];
    P[b] = a;
}

void print() {
    for(int i = 1; i <= N;i++) {
        cout << P[i] << " ";
    }cout << '\n';
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    cin >> N >> M >> Q;

    fill(P, P + 100001, -1);

    int from, to;
    long long answer = 0;

    for (int i = 1; i <= M; i++)
    {
        cin >> from >> to;
        graph[i] = { from, to };
        check[i] = true;
    }

    for (int i = 1; i <= Q; i++)
    {
        cin >> disconnect[i];
        check[disconnect[i]] = false;
    }

    for (int i = 1; i <= M; i++)
        if(check[i]) merge(graph[i].first, graph[i].second);
    print();
    for (int i = Q; i >= 1; i--)
    {
        int temp = disconnect[i];

        int a = find(graph[temp].first);
        int b = find(graph[temp].second);

        if (a != b) answer += ((long long)(P[a]) * (long long)(P[b]));

        merge(a, b);
    }

    print();
    cout << answer << '\n';

    return 0;
}*/