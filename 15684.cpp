/**
 * 15684: 사다리 조작
 * i 번째가 i가 나오도록
 * 이건 그냥 백트레킹 ? 어짜피 최대 설계 가능이 3개니까
 * 1개 설치시 가능한지 --> 1개로 모든 점에서 점 연결 후 확인
 * 2개 설치시 가능한지 --> ~ (백트래킹)
 * 3개 설치시 가능한지 --> ~ (백트래킹)
 *

 */

#include <iostream>

using namespace std;
#define MAX 50
int N, M, H, a, b, ans = -1, map[MAX][MAX];

void print_map() {
    cout << "\n--------------print map--------------\n";
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++)
            cout << j << " ";
        cout << '\n';
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M >> H; // N: 세로선 개수 1 ~ N, M: 가로선 개수 1 ~ M, H: 가로선 놓을 수 있는 위치 개수
    map.resize(N + 1);
    print_map();
    for (int i = 0; i < M; i++) {
        cin >> a >> b; // b번 & b+1번을 a번 점선 위치에서 연결 즉 a는 가로 b는 세로
        map[b][a] = 1;
    }

    return 0;
}