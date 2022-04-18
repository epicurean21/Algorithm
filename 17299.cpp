/**
 * 17299 오등큰수
 * 스택
 */
#include <iostream>
#include <stack>

using namespace std;
#define MAX 1000001
int N, A[MAX], cnt[MAX], ans[MAX];
stack<int> st;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> A[i];
        cnt[A[i]]++;
    }

    for (int i = N - 1; i >= 0; i--) {
        if (st.empty()) {
            st.push(A[i]);
            ans[i] = -1;
        } else if (cnt[A[i]] >= cnt[st.top()]) {
            while (true) {
                if (st.empty() || cnt[A[i]] < cnt[st.top()])
                    break;
                st.pop();
            }
            if (st.empty())
                ans[i] = -1;
            else
                ans[i] = st.top();
            st.push(A[i]);
        } else if(cnt[A[i]] < cnt[st.top()]) {
            ans[i] = st.top();
            st.push(A[i]);
        }
    }

    for(int i = 0; i < N; i++)
        cout << ans[i] << " ";

    return 0;
}