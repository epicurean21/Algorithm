#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;
#define MAX 500001
#define ll long long
int N, treeHeight, treeSize;
vector<pair<ll, int>> runner;
vector<ll> tree;

bool cmpSecond(const pair<ll, int> &a, const pair<ll, int> &b) {
    return a.second < b.second;
}

void init() {
    runner.resize(N);
    treeHeight = (int) ceil(log2(MAX));
    treeSize = 1 << (1 + treeHeight);
    tree.resize(treeSize);
}

void update(int node, int idx, int start, int end) {
    if (start > idx || end < idx)
        return;

    tree[node]++;

    if (start != end) {
        int m = (start + end) / 2;
        update(node * 2, idx, start, m);
        update(node * 2 + 1, idx, m + 1, end);
    } else
        return;
}

int query(int node, int start, int end, int left, int right) {
    if (right < start || left > end)
        return 0;
    if (start >= left && end <= right)
        return tree[node];

    int m = (start + end) / 2;
    return query(node * 2, start, m, left, right) + query(node * 2 + 1, m + 1, end, left, right);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N;
    init();
    for (int i = 0; i < N; i++) {
        cin >> runner[i].first;
        runner[i].second = i;
    }
    sort(runner.begin(), runner.end()); // 능력오름차순 정렬

    for (int i = 0; i < N; i++)
        runner[i].first = i;

    sort(runner.begin(), runner.end(), cmpSecond);

    for (int i = 0; i < N; i++) {
        int ans = i - query(1, 0, MAX, 0, runner[i].first) + 1;
        cout << ans << "\n";
        update(1, runner[i].first, 0, MAX);
    }
    return 0;
}