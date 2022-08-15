/**
 * 16457 단풍잎 이야기
 * 백트래킹, 탐색
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int n, m, k, skill, ans;
vector<vector<int>> quests;
vector<int> keySettings;

int countClearable() {
    int cnt = 0;
    for (int i = 0; i < m; i++) {
        bool flag = true;
        for (int j = 0; j < k; j++) {
            if (!binary_search(keySettings.begin(), keySettings.end(), quests[i][j])) {
                flag = false;
                break;
            }
        }
        if (flag)
            cnt++;
    }
    return cnt;
}

void clearQuests(int cnt, int cur) {
    if (cnt == n) {
        ans = max(countClearable(), ans);
        return;
    }

    for (int i = cur; i <= 2 * n; i++) {
        keySettings.push_back(i);
        clearQuests(cnt + 1, i + 1);
        keySettings.pop_back();
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m >> k;
    quests.resize(m + 1);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < k; j++) {
            cin >> skill;
            quests[i].push_back(skill);
        }
    }

    clearQuests(0, 1);
    cout << ans << "\n";

    return 0;
}