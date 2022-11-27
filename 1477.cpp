/**
 * 1477 휴게소 세우기
 * 이분 탐색
 */
#include <iostream>
#include <algorithm>

using namespace std;
#define MAX 1002
int N, M, L, map[MAX], ans;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M >> L;
    map[0] = 0, map[1] = L; // 시작 점, 끝 점
    for (int i = 2; i < N + 2; i++)
        cin >> map[i]; // 각 위치에 휴게소 위치 저장
    sort(map, map + N + 2); // 오름차순 정렬

    int l = 0, r = L;
    while (l <= r) {
        int m = (l + r) / 2;
        int cnt = 0;
        for (int i = 1; i < N + 2; i++) {
            int dist = map[i] - map[i - 1]; // 휴게소 위치 별 거리
            cnt += dist / m;
            if (dist % m == 0)
                cnt--;
        }
        if (cnt <= M) {
            r = m - 1;
            ans = m;
        } else
            l = m + 1;
    }

    cout << ans << '\n';
    return 0;
}