#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;
int N, K, cnt;
vector<int> num;
map<string, bool> chk;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> K;
    num.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> num[i];
    }
    sort(num.begin(), num.end());
    do {
        string tmp = "";
        for (int i = 0; i < K; i++)
            tmp += to_string(num[i]);

        if (chk.count(tmp))
            continue;

        chk[tmp] = true;
        cnt++;
    } while (next_permutation(num.begin(), num.end()));
    cout << cnt << "\n";
    return 0;
}