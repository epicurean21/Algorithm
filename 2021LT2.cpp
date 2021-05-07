#include <string>
#include <vector>
#include <algorithm>
#include <stack>
#include <iostream>

using namespace std;
#define MAX 100002
int sz, r[MAX], l[MAX];
stack<int> st, st2;

int absolute(int a) {
    return a < 0 ? (-1 * a) : a;
}

vector<int> solution(vector<int> array) {
    vector<int> answer;
    sz = array.size();
    answer.resize(sz);
    for (int i = sz - 1; i >= 0; i--) {
        if (st.empty()) {
            r[i] = -1;
            st.push(i);
        } else if (array[i] >= array[st.top()]) {
            while (1) {
                if (st.empty() || array[i] < array[st.top()])
                    break;
                st.pop();
            }
            if (st.empty()) {
                r[i] = -1;
                st.push(i);
            } else {
                r[i] = st.top();
                st.push(i);
            }
        } else if (array[i] < array[st.top()]) {
            r[i] = st.top();
            st.push(i);
        }
    }


    for (int i = 0; i < sz; i++) {
        if (st2.empty()) {
            l[i] = -1;
            st2.push(i);
        } else if (array[i] >= array[st2.top()]) {
            while (true) {
                if (st2.empty() || array[i] < array[st2.top()]) {
                    break;
                }
                st2.pop();
            }
            if (st2.empty()) {
                l[i] = -1;
                st2.push(i);
            } else {
                l[i] = st2.top();
                st2.push(i);
            }
        } else if (array[i] < array[st2.top()]) {
            l[i] = st2.top();
            st2.push(i);
        }
    }

    for (int i = 0; i < sz; i++) {
        if (l[i] == -1 && r[i] == -1) {
            answer[i] = -1;
            continue;
        } else if (l[i] == -1) {
            answer[i] = r[i];
            continue;
        } else if (r[i] == -1) {
            answer[i] = l[i];
            continue;
        }
        int left = absolute(i - l[i]);
        int right = absolute(i - r[i]);

        if (left < right)
            answer[i] = l[i];
        else if (left > right)
            answer[i] = r[i];
        else
            answer[i] = min(l[i], r[i]);
    }

    return answer;
}

int main() {
    vector<int> array = {3, 5, 4, 1, 2};
    vector<int> ans = solution(array);
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] << " ";
    }
    cout << '\n';
}