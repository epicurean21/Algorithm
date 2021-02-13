#include <iostream>
#include <vector>
#include <stack>

using namespace std;
int N, iter;
vector<int> A, lis;
vector<pair<int, int>> ans;
stack<int> st;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    A.resize(N);
    for (int i = 0; i < N; i++)
        cin >> A[i];
    lis.push_back(A[0]);
    ans.push_back({0, A[0]});
    iter = 1;
    for (int i = 1; i < N; i++) {
        if (lis[iter - 1] < A[i]) {
            lis.push_back(A[i]);
            ans.push_back({iter, A[i]});
            iter++;
        } else {
            int idx = upper_bound(lis.begin(), lis.end(), A[i]) - lis.begin();
            lis[idx] = A[i];
            ans.push_back({idx, A[i]});
        }
    }
//    for (int i = 0; i < ans.size(); i++)
//        cout << ans[i].first << " " << ans[i].second << '\n';
    int pos = iter - 1;
    for (int i = ans.size() - 1; i >= 0; i--) {
        int cur = ans[i].first;
        int curVal = ans[i].second;
        if (cur == pos) {
            st.push(curVal);
            pos--;
        }
    }
    cout << iter << "\n";
    while (!st.empty()) {
        cout << st.top() << " ";
        st.pop();
    }
    cout << '\n';
    return 0;
}
/*
8
1 6 2 5 7 3 5 6

 */