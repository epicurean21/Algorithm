#include <iostream>
#include <vector>

using namespace std;
#define MAX 51
int N, M, P, parent[MAX], person;
vector<vector<int>> map(MAX);
bool chk[MAX];

void init(int n) {
    for (int i = 1; i <= n; i++)
        parent[i] = i;
}

int find(int a) {
    if (parent[a] == a)
        return a;
    return parent[a] = find(parent[a]);
}

void merge(int a, int b) {
    int aa = find(a);
    int bb = find(b);
    parent[aa] = bb;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M >> P;
    init(N);
    for (int i = 0; i < P; i++) {
        cin >> person;
        chk[person] = true;
    }
    for (int i = 0; i < M; i++) {
        cin >> P;
        for (int j = 0; j < P; j++) {
            cin >> person;
            map[person].push_back(i);
        }
    }
    return 0;
}