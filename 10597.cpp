#include <iostream>
#include <vector>
#include <string>

using namespace std;
#define MAX 512
string kriii, tmp_s;
vector<int> tmp;
int N, tmp_n;
bool been[MAX];

void dfs(int cur) {
    if (cur == kriii.length()) {
        for (int i = 0; i < N; i++)
            cout << tmp[i] << " ";
        exit(0);
    }
    tmp_s = "";
    tmp_n = 0;
    for(int i = cur; i <= cur + 1; i++) {
        tmp_s = tmp_s + kriii[i];
        tmp_n = stoi(tmp_s);

        if(tmp_n > N || been[tmp_n]) continue;
        been[tmp_n] = true;
        tmp.push_back(tmp_n);
        dfs(i + 1);
        been[tmp_n] = false;
        tmp.pop_back();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> kriii;
    if (kriii.length() > 9)
        N = 9 + (kriii.length() - 9) / 2;
    else
        N = kriii.length();
    dfs(0);
    return 0;
}