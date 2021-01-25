#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
#define MAX 999999
int N, K, cnt;
vector<string> map;
vector<int> chk;
void dfs(int idx, int count) {
    if(count == K) {
        cnt++;
        return;
    }

    if(idx > N)
        return;
    for(int i = idx; i < N; i++) {
        dfs(i + 1, count + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> K;
    for (int i = 0; i < N; i++) {
        string a;
        cin >> a;
        map.push_back(a);
    }
    dfs(1, 0);
    cout << cnt << "\n";
    return 0;
}