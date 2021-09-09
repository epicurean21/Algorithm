/**
 * 15684: 사다리 조작
 * i 번째가 i가 나오도록
 * 이건 그냥 백트레킹 ? 어짜피 최대 설계 가능이 3개니까
 * 1개 설치시 가능한지 --> 1개로 모든 점에서 점 연결 후 확인
 * 2개 설치시 가능한지 --> ~ (백트래킹)
 * 3개 설치시 가능한지 --> ~ (백트래킹)
 *
 * 가로 세로를 뒤집자 ? map을 그릴때 vector emplace_back 을 쓰면서 가로로 늘어나게
 *
 */

#include <iostream>
#include <vector>

using namespace std;
#define MAX 280
int N, M, H, a, b, ans;
vector<vector<int>> map;

void print_map() {
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            cout << map[i][j] << " ";
        }
        cout << '\n';
    }
}

void init(int n, int m) {
    map.resize(m + 1);
    for (int i = 1; i <= n; i++) {
        map[i].emplace_back()
    }

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M >> H; // N: 세로선 개수 1 ~ N, M: 가로선 개수 1 ~ M, H: 가로선 놓을 수 있는 위치 개수

    init(N, M);
    print_map();
    for (int i = 0; i < M; i++) {
        cin >> a >> b; // b번 & b+1번을 a번 점선 위치에서 연결 즉 a는 가로 b는 세로

    }

    return 0;
}