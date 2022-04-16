/**
 * 17298 오큰수 : 자료구조, 스택
 * 스택을 이용해서 보다 빠르게 값을 찾을 수 있다 (O(N))
 * 제한 조건 수열의 크기가 100만이기 때문에, 각 원소의 오른쪽 위치에 존재하는 원소들이 본인보다 큰 걸 찾는데
 * naive 하게 돌면 O(N^2) 으로 시간초과가 난다.
 *
 * 스택을 이용해서 수열의 제일 끝 에서부터 정답을 찾아나간다.
 * 현재 스택에 올라있는 top 값 (수열의 인덱스) 보다 자신이 작다면, 정답은 해당 인덱스이고 스택에는 자신을 넣는다
 * 현재 스택에 올라있는 top 값 (수열의 인덱스) 보다 자신이 크거나 같다면, 정답은 while문을 돌면서 해당 스택에 top값이 자신보다 클때까지 돌린다.
 * - while문이 끝나고 스택이 비었다면 본인의 오큰수가 없기에 -1, 비어있지 않다면 해당 top index가 정답
 */
#include <iostream>
#include <stack>

using namespace std;
#define MAX 1000001
int A[MAX], N, ans[MAX];
stack<int> st;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N;
    for (int i = 0; i < N; i++)
        cin >> A[i];

    for (int i = N - 1; i >= 0; i--) { // 8 4 5 9 순서
        if (st.empty()) { // N - 1
            ans[i] = -1;
            st.push(i);
        } else if(A[i] >= A[st.top()]) {
            while(true) {
                if(st.empty() || A[i] < A[st.top()])
                    break;
                st.pop();
            }

            if(st.empty()) {
                ans[i] = -1;
                st.push(i);
            } else {
                ans[i] = st.top();
                st.push(i);
            }
        } else if(A[i] < A[st.top()]) {
            ans[i] = st.top();
            st.push(i);
        }
    }

    for(int i =0; i< N; i++)
        cout << (ans[i] == -1 ? -1 : A[ans[i]]) << " ";

    return 0;
}