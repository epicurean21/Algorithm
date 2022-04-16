/**
 * 3015 오아시스 재결합
 * 스택, 수학
 */
#include <iostream>
#include <stack>

using namespace std;
#define ll long long
ll N, h, ans, tmp;
stack<pair<ll, ll>> st;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> h;
        tmp = 1;

        while (!st.empty()) {
            if (st.top().first < h) {
                ans += st.top().second;
                tmp = 1;
                st.pop();
            } else if (st.top().first == h) {
                ans += st.top().second;
                tmp = st.top().second + 1;
                st.pop();
            } else {
                ans++;
                break;
            }
        }
        st.push({h, tmp});
    }

    cout << ans << '\n';

    return 0;
}