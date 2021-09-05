/**
 * 2170: 선긋기
 * 스위핑?? 정렬 ??
 *
 * 내가생각한 아이디어
 * 두 점이 들어왔을 때
 * 최소, 최댓 값의 변경 ?
 * a, b, c , d
 * 1 3 2 4
 * 가장 깔끔 계산: 기존 최대보다 c가 큼, 기존 최소보다 d가 작음
 *
 * 기존 최대 3보다 새로운 값 c가 작음 --> 그러면 기존의 최소와 비교 ?
 *
 * case 1: 기존 선분과 안겹침 --> 그냥 더하면 된다
 */
#include <iostream>

using namespace std;

int N, x, y, cur_min = INT32_MAX, cur_max, ans;

int min(int a, int b) {
    return a > b ? b : a;
}

int max(int a, int b) {
    return a > b ? a : b;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    for (int i = 0; i < N; i++) {
        cin >> x >> y;

        if (cur_max < x || cur_min > y) { // 기존 최대보다 큰 x, 기존 최소보다 작은 y
            ans += y - x;
            continue;
        }


    }
    return 0;
}