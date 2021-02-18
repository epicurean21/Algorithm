#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <sstream>

using namespace std;
#define MAX 27
vector<vector<int>> map(MAX);
int indeg[MAX], chk[MAX], ans, cost[MAX];
queue<int> q;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    string str;
    while (getline(cin, str)) {
        stringstream input(str);
        char there;
        int a;
        string from;
        input >> there >> a >> from;
        cost[there - 'A'] = a;
        for (int l = 0; l < from.length(); l++) {
            map[str[l] - 'A'].push_back(there);
            indeg[there - 'A']++;
        }
    }

    for (int i = 0; i <= 26; i++)
        if (indeg[i] == 0)
            q.push(i);

    while (!q.empty()) {
        int cur = q.front();
        ans += cost[cur];
        q.pop();
        for (int i = 0; i < map[cur].size(); i++) {

        }
    }
    return 0;
}
