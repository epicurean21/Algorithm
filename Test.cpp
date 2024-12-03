#include "bits/stdc++.h"

using namespace std;
#define MAX 1001
int N, M, K, A[MAX][MAX], x, y, z, field[MAX][MAX],
        dx[] = {1, 1, 0, -1, -1, -1, 0, 1},
        dy[] = {0, 1, 1, 1, 0, -1, -1, -1};
vector <pair<int, pair < int, int>>>
trees;
vector <pair<int, pair < int, int>>>
dead_trees;

void spring() {
    sort(trees.begin(), trees.end());

    for (int i = 0; i < trees.size(); i++) {
        int age = trees[i].first;
        int c = trees[i].second.first;
        int r = trees[i].second.second;

        if (field[r][c] < age) {
            dead_trees.push_back(trees[i]);
        } else {
            field[r][c] -= age;
            trees[i].first += 1;
        }
    }

    vector < pair < int, pair < int, int>>> temp;
    for (int i = 0; i < trees.size(); i++) {
        if (trees[i].first != -1) {
            temp.push_back(trees[i]);
        }
    }

    trees = temp;
}

void summer() {
    if (dead_trees.empty()) {
        return;
    }
    for (int i = 0; i < dead_trees.size(); i++) {
        int age = dead_trees[i].first;
        int position_x = dead_trees[i].second.first;
        int position_y = dead_trees[i].second.second;

        int nutrient = age / 2;
        A[position_y][position_x] += nutrient;
    }
    dead_trees.clear();
}

void autumn() {
    int trees_count = trees.size();
    for (int i = 0; i < trees_count; i++) {
        int age = trees[i].first;
        if (age % 5) {
            continue;
        }
        int position_x = trees[i].second.first;
        int position_y = trees[i].second.second;

        for (int k = 0; k < 8; k++) {
            int next_x = position_x + dx[k];
            int next_y = position_y + dy[k];

            if (next_x < 1 || next_x > N || next_y < 1 || next_y > N) continue;

            trees.push_back({1, {next_x, next_y}});
        }
    }
}

void winter() {
    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            field[i][j] += A[i][j];
}

void print_tree_list() {
    for (int i = 0; i < trees.size(); i++) {
        cout << "x: " << trees[i].second.first << ", y: " << trees[i].second.second << ", age: " << trees[i].first
             << '\n';
    }
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
        trees.push_back({z, {x, y}});
    }

    while (K--) {
        if (trees.empty()) break;
        spring();
        summer();
        autumn();
        winter();
    }

    cout << trees.size() << '\n';
    return 0;
}