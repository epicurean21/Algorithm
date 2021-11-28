#include <iostream>
#include <stack>

using namespace std;
int N, height, max_height, ans;
stack<int> st;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    ans = N - 1;

    for (int i = 0; i < N; i++) {
        cin >> height;

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