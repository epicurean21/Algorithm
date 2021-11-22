/**
 * 2104 부분배열 고르기
 * 스택활용 풀이
 */

#include <iostream>
#include <stack>

using namespace std;
typedef long long ll;

ll s, temp, v;
int n;
stack<pair<int, ll>> st;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> v;
        temp = 0;
        while (!st.empty() && v < st.top().first) {
            temp += st.top().second;
            s = max(s, temp * st.top().first);
            st.pop();
        }
        temp += v;
        st.emplace(v, temp);
    }
    temp = 0;
    while (!st.empty()) {
        temp += st.top().second;
        s = max(s, temp * st.top().first);
        st.pop();
    }
    cout << s << '\n';
    return 0;
}