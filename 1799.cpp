/**
 * 1799 비숍
 * 기존 n queen과의 차이점은, 가로 세로를 안보고 대각선만 본다.
 * 단순히 방법을 생각하면, dfs + 백트래킹.. 그런 경우 모든 곳에 queen을 둘 수 있다면, O(2^N^N) 시간초과다
 * 대각선만 보는 방법으로 최적화를 하면된다. 대각선을 두 종류로 나누어서 탐색하면 훨씬 빠르다.
 * 어짜피 서로 공격할 수 없는 위치가 두 종류다
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
#define MAX 11
int N, map[MAX][MAX], ans_type1, ans_type2;
vector<pair<int, int>> queens;
bool visited[MAX][MAX];

int max(int a, int b) { return a > b ? a : b; }

bool isEven(int a) {
    return a == 0 || a % 2;
}

bool possible(int x, int y) {
    int dx = x + 1;
    int dy = y - 1;
    while (dx < N && dy >= 0) {
        if (visited[dy][dx]) return false; // queen 존재
        dx++;
        dy--;
    }

    dx = x - 1;
    dy = y - 1;
    while (dx >= 0 && dy >= 0) {
        if (visited[dy][dx]) return false;
        dx--;
        dy--;
    }

    return true;
}

void check_map_type1(int queen, int cnt) { // 검정색 맵
    ans_type1 = max(ans_type1, cnt);

    for (int i = queen; i < queens.size(); i++) {
        int x = queens[i].first;
        int y = queens[i].second;

        if ((isEven(x) && isEven(y)) || (!isEven(x) && !isEven(y))) { // 짝수행 짝수열 && 홀수행 홀수열
            if (!visited[y][x] && possible(x, y)) {
                visited[y][x] = true;
                check_map_type1(i + 1, cnt + 1);
                visited[y][x] = false;
            }
        }
    }
}

void check_map_type2(int queen, int cnt) { // 흰색 맵
    ans_type2 = max(ans_type2, cnt);

    for (int i = queen; i < queens.size(); i++) {
        int x = queens[i].first;
        int y = queens[i].second;

        if ((isEven(x) && !isEven(y)) || (!isEven(x) && isEven(y))) { // 짝수행 홀수열 && 홀수행 짝수열
            if (!visited[y][x] && possible(x, y)) { // 1이 아니면서 둘 수 있다면
                visited[y][x] = true;
                check_map_type2(i + 1, cnt + 1);
                visited[y][x] = false;
            }
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> map[i][j];
            if (map[i][j]) queens.emplace_back(j, i); // 놓을 수 있는 위치 저장
        }
    }
    sort(queens.begin(), queens.end());

    check_map_type1(0, 0);
    check_map_type2(0, 0);
    cout << ans_type1 + ans_type2 << '\n';
    return 0;
}