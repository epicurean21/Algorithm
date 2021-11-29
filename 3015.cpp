/**
 * 3015 오아시스 재결합
 * 스택, 수학
 */

#include <iostream>
#include <stack>

using namespace std;
int N, height, max_height = INT32_MAX, ans;
stack<int> st;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;

    for (int i = 0; i < N; i++) {
        cin >> height;

        if (st.empty() && (height <= max_height)) {
            st.push(height);
            max_height = st.top();
        } else {
            while (st.top() >= height) {

            }
        }
        if (st.empty()) {
            st.push(height);
            max_height = height;
        } else {
            if (height >= max_height) {
                ans++;
                max_height = height;
            } else {
                st.pop();
                st.push(max_height);
                max_height = height;
            }
        }
    }

    cout << ans << '\n';
    return 0;
}