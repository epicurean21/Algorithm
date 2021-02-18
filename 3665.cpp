#include <iostream>
#include <cstring>
#include <queue>
#include <vector>

using namespace std;
#define MAX 501
int T, n, m, a, b;
int ranking[MAX], idg[MAX];
bool impossible, chk[MAX][MAX];
queue<int> q;
vector<int> ans;

void init() {
    impossible = false;
    memset(chk, false, sizeof(chk));
    memset(idg, 0, sizeof(idg));
    ans.clear();
    while (!q.empty())
        q.pop();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> T;
    while (T--) {
        init();
        cin >> n;
        for (int i = 0; i < n; i++)
            cin >> ranking[i]; // 5 -> 4 -> 3->  2-> 1
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                chk[ranking[i]][ranking[j]] = true;
                idg[ranking[j]]++;
            }
        }
        cin >> m;
        for (int i = 0; i < m; i++) {
            cin >> a >> b;
            if (chk[a][b] == true) { // 지난대회 a > b
                chk[a][b] = false;
                chk[b][a] = true;
                idg[a]++;
                idg[b]--;
            } else {
                chk[b][a] = false;
                chk[a][b] = true;
                idg[b]++;
                idg[a]--;
            }
        }
        for (int i = 1; i <= n; i++)
            if (!idg[i])
                q.push(i);

        for (int i = 0; i < n; i++) {
            if (q.empty())
                break;

            int cur = q.front();
            q.pop();
            ans.push_back(cur);
            idg[cur]--;
            for (int j = 1; j <= n; j++) {
                if (chk[cur][j] == true)
                    idg[j]--;
                if (idg[j] == 0)
                    q.push(j);
            }
        }
        if (ans.size() == n) {
            for (int i = 0; i < n; i++)
                cout << ans[i] << " ";
            cout << '\n';
        } else
            cout << "IMPOSSIBLE\n";

    }
    return 0;
}