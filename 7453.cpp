#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define MAX 4001
#define ll long long
int N, A[MAX], B[MAX], C[MAX], D[MAX];
ll cnt;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> A[i] >> B[i] >> C[i] >> D[i];
    }

    vector<ll> tmp;
    for (int k = 0; k < N; k++) {
        for (int f = 0; f < N; f++) {
            tmp.push_back((C[k] + D[f]));
        }
    }
    sort(tmp.begin(), tmp.end());

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            ll m = A[i] + B[j];
            // l은 lower bound로 A[a] + B[b] 보다 같거나 큰 값이 처음 나오는 위치
            ll l = lower_bound(tmp.begin(), tmp.end(), -m) - tmp.begin();
            // h는 upper bound로 A[a] + B[b] 보다 큰 값이 처음으로 나오는 위치
            ll h = upper_bound(tmp.begin(), tmp.end(), -m) - tmp.begin();

            if (-m == tmp[l])
                cnt += (h - l);
        }
    }

    cout << cnt << '\n';
    return 0;
}