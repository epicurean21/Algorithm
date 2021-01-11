#include<iostream>
#include<string>
#include<algorithm>
#define MAX 16
using namespace std;
int L, C;
char cipher[MAX];

void dfs(int idx, int cnt, int vo, int ja, string str) {
    if (cnt == L) {
        if (vo >= 1 && ja >= 2)
            cout << str << "\n";
        return;
    }
    if (idx == C) return;
    if (cipher[idx] == 'a' || cipher[idx] == 'e' || cipher[idx] == 'i' || cipher[idx] == 'o' || cipher[idx] == 'u')
        dfs(idx + 1, cnt + 1, vo + 1, ja, str + cipher[idx]);
    else
        dfs(idx + 1, cnt + 1, vo, ja + 1, str + cipher[idx]);
    dfs(idx + 1, cnt, vo, ja, str);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> L >> C;
    for (int i = 0; i < C; i++)
        cin >> cipher[i];
    sort(cipher, cipher + C);
    dfs(0, 0, 0, 0, "");
    return 0;
}