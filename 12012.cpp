/**
 * Closing the Farm
 * - Data Structure
 * - Disjoint Set (Union-Find)
 * - Offline Query
 */
#include <iostream>

using namespace std;
#define MAX 200001
int N, M, p[MAX], a, b;

int find(int a) {
    if (p[a] == a)
        return a;
    return p[a] = find(p[a]);
}

void merge(int a, int b) {
    int aa = find(a);
    int bb = find(b);
    p[aa] = bb;
}

void init(int N) {
    for (int i = 1; i <= N; i++)
        p[i] = i;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;

    init(N);

    for (int i = 0; i < M; i++) {
        cin >> a >> b;
        merge(a, b);
    }

    int cnt = 1;
    for (int i = 0; i < N; i++) {

    }
    return 0;
}