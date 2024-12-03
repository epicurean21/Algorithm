#include "bits/stdc++.h"

using namespace std;
#define MAX 11
int N, M, K, A[MAX][MAX], x, y, z, field[MAX][MAX], ans,
        dx[] = {1, 1, 0, -1, -1, -1, 0, 1},
        dy[] = {0, 1, 1, 1, 0, -1, -1, -1};
vector<int> tree_list[MAX][MAX];

void springAndSummer() {
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (tree_list[i][j].empty()) continue;

            int nutrient = 0;
            vector<int> temp;

            sort(tree_list[i][j].begin(), tree_list[i][j].end());

            for (int k = 0; k < tree_list[i][j].size(); k++) {
                int age = tree_list[i][j][k];

                if (field[i][j] >= age) {
                    field[i][j] -= age;
                    temp.push_back(age + 1);
                } else {
                    nutrient += age / 2;
                }
            }

            tree_list[i][j].clear();
            for (int k: temp) {
                tree_list[i][j].push_back(k);
            }
            field[i][j] += nutrient;
        }
    }
}

void autumn() {
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            if (tree_list[i][j].empty()) continue;

            for (int k = 0; k < tree_list[i][j].size(); k++) {
                int age = tree_list[i][j][k];
                if (age % 5) continue;
                for (int f = 0; f < 8; f++) {
                    int next_x = j + dx[f];
                    int next_y = i + dy[f];
                    if (next_x < 1 || next_x > N || next_y < 1 || next_y > N) continue;

                    tree_list[next_y][next_x].push_back(1);
                }
            }
        }
    }
}

void winter() {
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            field[i][j] += A[i][j];
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> N >> M >> K;

    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++) {
            field[i][j] = 5;
            cin >> A[i][j];
        }

    for (int i = 0; i < M; i++) {
        cin >> y >> x >> z;
        tree_list[y][x].push_back(z);
    }

    while (K--) {
        springAndSummer();
        autumn();
        winter();
    }

    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            ans += tree_list[i][j].size();

    cout << ans << '\n';

    return 0;
}