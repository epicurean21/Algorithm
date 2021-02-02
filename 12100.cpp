#include <iostream>
#include <algorithm>
#include <stack>
#include <queue>

using namespace std;
#define MAX 22
int N, map[MAX][MAX], ans;

int max(int a, int b) {
    return a > b ? a : b;
}

int findMax() {
    int tmp = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            tmp = max(map[i][j], tmp);
    return tmp;
}

void moveUp() { //  1
    stack<int> st;
    for (int i = 0; i < N; i++) {
        // 세로로 한 줄씩 처리하자
        for (int j = N - 1; j >= 0; j--) {
            if (map[j][i] != 0) {
                st.push(map[j][i]);
                map[j][i] = 0;
            }
        }

        if (st.empty()) continue;
        if (st.size() == 1) {
            map[0][i] = st.top();
            st.pop();
            continue;
        }
        queue<int> q;
        while (!st.empty()) {
            int a = st.top();
            st.pop();
            if (st.empty()) {
                q.push(a);
                continue;
            }
            int b = st.top();
            st.pop();
            if (a == b)
                q.push(a + b);
            else {
                q.push(a);
                st.push(b);
            }
        }

        int tmp = 0;
        for (int j = 0; j < N; j++) {
            if (!q.empty()) {
                tmp = q.front();
                q.pop();
            } else
                tmp = 0;
            map[j][i] = tmp;
        }
    }
}

void moveDown() { // 2
    stack<int> st;
    for (int i = 0; i < N; i++) {
        // 세로로 한 줄씩 처리하자
        for (int j = 0; j < N; j++) {
            if (map[j][i] != 0) {
                st.push(map[j][i]);
                map[j][i] = 0;
            }
        }

        if (st.empty()) continue;
        if (st.size() == 1) {
            map[N - 1][i] = st.top();
            st.pop();
            continue;
        }
        queue<int> q;
        while (!st.empty()) {
            int a = st.top();
            st.pop();
            if (st.empty()) {
                q.push(a);
                continue;
            }
            int b = st.top();
            st.pop();
            if (a == b)
                q.push(a + b);
            else {
                q.push(a);
                st.push(b);
            }
        }

        int tmp = 0;
        for (int j = N - 1; j >= 0; j--) {
            if (!q.empty()) {
                tmp = q.front();
                q.pop();
            } else
                tmp = 0;
            map[j][i] = tmp;
        }
    }
}

void toRight() { // 3
    stack<int> st;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (map[i][j] != 0) {
                st.push(map[i][j]);
                map[i][j] = 0;
            }
        }

        if (st.empty()) continue;
        if (st.size() == 1) {
            map[i][N - 1] = st.top();
            st.pop();
            continue;
        }
        queue<int> q;
        while (!st.empty()) {
            int a = st.top();
            st.pop();
            if (st.empty()) {
                q.push(a);
                continue;
            }
            int b = st.top();
            st.pop();
            if (a == b)
                q.push(a + b);
            else {
                q.push(a);
                st.push(b);
            }
        }
        int tmp = 0;
        for (int j = N - 1; j >= 0; j--) {
            if (!q.empty()) {
                tmp = q.front();
                q.pop();
            } else
                tmp = 0;
            map[i][j] = tmp;
        }
    }
}

void toLeft() { // 4
    stack<int> st;
    for (int i = 0; i < N; i++) {
        for (int j = N - 1; j >= 0; j--) {
            if (map[i][j] != 0) {
                st.push(map[i][j]);
                map[i][j] = 0;
            }
        }

        if (st.empty()) continue;
        if (st.size() == 1) {
            map[i][0] = st.top();
            st.pop();
            continue;
        }
        queue<int> q;
        while (!st.empty()) {
            int a = st.top();
            st.pop();
            if (st.empty()) {
                q.push(a);
                continue;
            }
            int b = st.top();
            st.pop();
            if (a == b)
                q.push(a + b);
            else {
                q.push(a);
                st.push(b);
            }
        }
        int tmp = 0;
        for (int j = 0; j < N; j++) {
            if (!q.empty()) {
                tmp = q.front();
                q.pop();
            } else
                tmp = 0;
            map[i][j] = tmp;
        }
    }
}

void dfs(int cnt) {
    if (cnt == 10) {
        ans = max(findMax(), ans);
        return;
    }

    int tmp[MAX][MAX];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            tmp[i][j] = map[i][j];

    for (int i = 0; i < 4; i++) {
        switch (i) {
            case 0:
                moveUp();
                break;
            case 1:
                moveDown();
                break;
            case 2:
                toRight();
                break;
            case 3:
                toLeft();
        }
        dfs(cnt + 1);
        for (int j = 0; j < N; j++)
            for (int k = 0; k < N; k++)
                map[j][k] = tmp[j][k];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    // 중복순열은 DFS를 통해 하자 , 1 1 1 1 1 , 1 1 1 1 2 , 1 1 1 1 1 3, ~~~ 4 4 4 4 4 3, 4 4 4 4 4
    cin >> N;
    for (int i = 0; i < N; i++) // y축
        for (int j = 0; j < N; j++) // x 축
            cin >> map[i][j];
    dfs(0);
    cout << ans << '\n';
    return 0;
}