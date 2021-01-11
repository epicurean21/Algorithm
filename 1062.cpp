#include <iostream>
#include <string>

using namespace std;
#define MAX 51
int N, K, ans;
bool alpha[26];
string vc[MAX];

void init() { // a, n, t, i, c
    alpha['a' - 'a'] = true;
    alpha['c' - 'a'] = true;
    alpha['n' - 'a'] = true;
    alpha['t' - 'a'] = true;
    alpha['i' - 'a'] = true;
}
int max(int a, int b) {
    return a > b ? a : b;
}

void dfs(int cur, int cnt) {
    if(cnt == K) { // K개 만큼 학습 끝
        int cntAns = 0;
        for(int i = 0; i < N; i++) {
            bool flag = false;
            for(int j = 0; j < vc[i].length(); j++) {
                if(!alpha[vc[i][j] - 'a']) {
                    flag = true;
                    break;
                }
            }
            if(!flag)
                cntAns++;
        }
        ans = max(ans, cntAns);
        return;
    }

    for(int i = cur; i < 26; i++) {
        if(!alpha[i]) {
            alpha[i] = true;
            dfs(i, cnt + 1);
            alpha[i] = false;
        }
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> K;
    for (int i = 0; i < N; i++) {
        cin >> vc[i];
        string tmp1 = vc[i];
        string tmp2 = "";
        for(int i = 4; i < tmp1.length() - 5; i++)
            tmp2 += tmp1;
    }

    if (K < 5 || K == 26) {
        if (K < 5)
            cout << "0\n";
        else if (K == 26)
            cout << N << "\n";
    } else {
        K -= 5; // a, n, t, i, c
        init();
        dfs(0, 0);
        cout << ans << "\n";
    }
    return 0;
}