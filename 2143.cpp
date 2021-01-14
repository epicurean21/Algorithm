#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define MAX 1001
#define ll long long
int T, N, M;
int A[MAX], B[MAX];
vector<int> aSum, bSum;

int main() {
    cin >> T >> N;
    for (int i = 0; i < N; i++)
        cin >> A[i];
    cin >> M;
    for (int i = 0; i < M; i++)
        cin >> B[i];

    for (int i = 0; i < N; i++) {
        int sum = A[i];
        aSum.push_back(sum);
        for (int j = i + 1; j < N; j++) {
            sum += A[j];
            aSum.push_back(sum);
        }
    }

    for (int i = 0; i < M; i++) {
        int sum = B[i];
        bSum.push_back(sum);
        for (int j = i + 1; j < M; j++) {
            sum += B[j];
            bSum.push_back(sum);
        }
    }

    sort(bSum.begin(), bSum.end());
    ll ans = 0;
    for (int i = 0; i < aSum.size(); i++) {
        int target = T - aSum[i];
        int low = lower_bound(bSum.begin(), bSum.end(), target) - bSum.begin();
        int high = upper_bound(bSum.begin(), bSum.end(), target) - bSum.begin();
        ans += (high - low);
    }

    cout << ans << "\n";
}