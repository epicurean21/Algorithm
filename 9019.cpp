#include <iostream>
#include <vector>
#include <queue>

using namespace std;
#define MAX 10001
#define MOD 10000
int T, s, e;
bool been[MAX];
queue<pair<int, string>> q;

void reset() {
    for (int i = 0; i < MAX; i++)
        been[i] = false;

    while (!q.empty())
        q.pop();
}

string bfs(int start, string str) {
    q.push({start, str});
    been[start] = true;
    while (!q.empty()) {
        int curN = q.front().first;
        string curS = q.front().second;
        q.pop();

        if (curN == e)
            return curS;
        else {
            int D = (curN * 2) % MOD;
            int S;
            if (curN != 0)
                S = curN - 1;
            else
                S = 9999;
            int L = (curN % 1000) * 10 + (curN / 1000);
            int R = (curN % 10) * 1000 + (curN / 10);

            if(!been[D]) {
                q.push({D, curS + "D"});
                been[D] = true;
            }
            if(!been[S]) {
                q.push({S, curS + "S"});
                been[S] = true;
            }
            if(!been[L]){
                q.push({L, curS + "L"});
                been[L] = true;
            }
            if(!been[R]) {
                q.push({R, curS + "R"});
                been[R] = true;
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> T;
    while (T--) {
        cin >> s >> e;
        cout << bfs(s, "") << "\n";
        reset();
    }
    return 0;
}