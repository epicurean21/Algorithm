#include <iostream>
#include <cmath>
#include <vector>

using namespace std;
#define ll long long
// 구간 합 구하기2 (10999)
int N, M, K, a, b, c;
vector<ll> tree, arr, lazy;

void print() {
    cout << "\n-----tree print-----\n";
    for (int i = 0; i < tree.size(); i++) {
        cout << tree[i] << " ";
    }
    cout << '\n';
}

ll construct_tree(int node, int start, int end) {
    if (start == end)
        return tree[node] = arr[start];

    int m = (start + end) / 2;
    return tree[node] = construct_tree(node * 2, start, m) + construct_tree(node * 2 + 1, m + 1, end);
}

void update_lazy(int node, int start, int end) {
    if (lazy[node] == 0)
        return;

    // 자식 노드가 있는 수 만큼 lazy값에 곱하여 더한다.
    tree[node] += (end - start + 1) * lazy[node];

    //leaf가 아니라면 자식에게 lazy 물려주기
    if (start != end) {
        lazy[node * 2] += lazy[node];
        lazy[node * 2 + 1] += lazy[node];
    }

    lazy[node] = 0;
}

void update(int node, int start, int end, int left, int right, ll diff) {
    /*
        순서
        1. lazy가 존재하면 업데이트 해준다.(tree[node] 변화)
        2. val을 더해준다.(자식수가 있는 만큼)
        2에서 자식 수만큼 더해주는 이유는 자식들은 아직 lazy가 업데이트 되지 않았기 때문
    */
    update_lazy(node, start, end);

    // 범위 밖
    if (start > right || end < left)
        return;

    // 원하는 구간 안에 있는 경우
    if (start >= left && end <= right) {
        tree[node] += (end - start + 1) * diff;
        if (start != end) {
            lazy[node * 2] += diff;
            lazy[node * 2 + 1] += diff;
        }
        return;
    }

    int m = (start + end) / 2;
    update(node * 2, start, m, left, right, diff);
    update(node * 2 + 1, m + 1, end, left, right, diff);

    // 구간이 걸쳐서 속해 있다면 자식 노드를 이용하여 부모 노드를 업데이트 한다
    tree[node] = tree[node * 2] + tree[node * 2 + 1];
}

ll sum(int node, int start, int end, int left, int right) {
    /* update이후 남은 lazy를 해당하는 구간을 sum 할 때 업데이트 해준다.

    update만 주구장창 하게 되면 update_range에 의해 남은 lazy가 생길 수 있다.
    따라서 sum을 할 때 lazy가 존재하는지 최종적으로 체크 한 후
    일반적인 세그트리 합과 같은 방식으로 구현하면 된다.
    */
    update_lazy(node, start, end);

    if (start > right || end < left)
        return 0;

    if (start >= left && end <= right)
        return tree[node];

    int m = (start + end) / 2;
    return sum(node * 2, start, m, left, right) + sum(node * 2 + 1, m + 1, end, left, right);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M >> K;
    int h = (int) ceil(log2(N + 1));
    tree.resize(1 << h + 1);
    lazy.resize(1 << h + 1);
    arr.resize(N + 1);
    for (int i = 1; i <= N; i++)
        cin >> arr[i];

    construct_tree(1, 1, N);
    //print();
    for (int i = 0; i < M + K; i++) {
        cin >> a;
        if (a == 1) { // update !
            ll d;
            cin >> b >> c >> d; // b ~ c 구간에 d를 더해라
            update(1, 1, N, b, c, d);
            //print();
        } else if (a == 2) { // 구간 합 구하기
            cin >> b >> c;
            cout << sum(1, 1, N, b, c) << '\n';
        }
    }
    return 0;
}