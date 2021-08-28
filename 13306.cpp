#include <iostream>

using namespace std;
#define MAX 200001
int N, Q, a, x, c, b, d;
int p[MAX];

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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> Q;

    for (int i = 1; i <= N; i++)
        p[i] = i;

    for (int i = 0; i < N; i++) {
        cin >> a;
        merge(i + 1, a);
    }

    return 0;
}