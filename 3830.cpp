#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
#define MAX 100001
#define ll long long

int n, m;
int pr[MAX];
ll weight[MAX];

int findf(int a) {
    if (a == pr[a])
        return a;
    int aa = pr[a];
    pr[a] = findf(pr[a]);
    weight[a] += weight[aa];
    return pr[a];
}

//b가 a보다 무거울경우
void unionf(int a, int b, int w) {
    findf(a); // union 하면서 자신이 루트가 아니라면 무개를 추가 해준다.
    findf(b);
    ll x = weight[a];
    ll y = weight[b];
    int roota = findf(a);
    int rootb = findf(b);
    pr[rootb] = roota;
    weight[rootb] = x + w - y;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    while (true) {
        cin >> n >> m;
        if (n == 0 && m == 0)
            break;
        for (int i = 1; i <= n; i++) {
            pr[i] = i;
            weight[i] = 0;
        }

        for (int i = 0; i < m; i++) {
            char com;
            int a, b, w;
            cin >> com;
            if (com == '!') {
                cin >> a >> b >> w;
                unionf(a, b, w);
            } else {
                cin >> a >> b;
                if (findf(a) == findf(b))
                    cout << weight[b] - weight[a] << '\n';
                else
                    cout << "UNKNOWN\n";
            }
        }
    }

    return 0;
}