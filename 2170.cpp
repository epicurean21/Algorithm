/**
 * 2170: 선긋기
 * 스위핑?? 정렬 ??
 *
 * case 1: 기존 선분과 안겹침 --> 그냥 더하면 된다
 * case 2: 기존 선분과 완전히 겹친다 --> 무시
 * case 3: 기존 선분과 일부만 겹침 (작거나, 크거나) --> 부분 더해주기
 *
 * 들어오는 값들을 오름차순 정렬을 통해 최대한 중간에 겹치는 부분이 없도록,
 * 예를 들어 (1, 3), (6, 8) 이어서 현재 길이가 2 + 2로 4인데 다음 값이 (4, 5) 면 계산하기 병맛
 * 정렬을 해주고, 세 가지 케이스에 맞게 계산해준다 좆밥이네
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