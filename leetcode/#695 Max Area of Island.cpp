/**
 * Leetcode #695 Max Area of Island
 * Breadth First Search (BFS) / DFS
 */
#include "../bits/stdc++.h"

using namespace std;

class Solution {
public:
    bool visited[51][51]{};
    int dx[4] = {0, 1, 0, -1}, dy[4] = {1, 0, -1, 0};

    int solve(vector<vector<int>> &grid, int x, int y) {
        queue<pair<int, int>> q;
        q.push({x, y});
        int cnt = 0;
        while (!q.empty()) {
            pair<int, int> cur = q.front();
            q.pop();
            if (visited[cur.second][cur.first]) continue;
            visited[cur.second][cur.first] = true;
            cnt++;

            for (int i = 0; i < 4; i++) {
                int nx = cur.first + dx[i];
                int ny = cur.second + dy[i];

                if (nx < 0 || nx >= grid[0].size() || ny < 0 ||
                    ny >= grid.size())
                    continue;
                if (grid[ny][nx] != 1)
                    continue;
                if (visited[ny][nx])
                    continue;

                q.push({nx, ny});
            }
        }
        return cnt;
    }

    int maxAreaOfIsland(vector<vector<int>> &grid) {
        int ans = 0;
        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[i].size(); j++) {
                if (grid[i][j] != 1 || visited[i][j]) continue;

                ans = max(ans, solve(grid, j, i));
            }
        }
        return ans;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    Solution s = *new Solution();
    vector<vector<int>> grid = {{1, 1, 0, 0, 0},
                                {1, 1, 0, 0, 0},
                                {0, 0, 0, 1, 1},
                                {0, 0, 0, 1, 1}};

    cout << s.maxAreaOfIsland(grid) << '\n';
    return 0;
}