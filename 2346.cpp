/**
 * 2346 풍선 터트리기
 * 자료구조, 덱 (deque)
 */
#include <iostream>
#include <deque>

using namespace std;
int N, num, cnt;
deque<pair<int, int>> balloons;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    for (int i = 1; i <= N; i++) {
        cin >> num;
        balloons.emplace_back(num, i);
    }

    while (!balloons.empty()) {
        cnt = balloons.front().first;
        cout << balloons.front().second << " ";
        balloons.pop_front();
        if (cnt > 0) {
            for (int i = 0; i < cnt - 1; i++) {
                balloons.push_back(balloons.front());
                balloons.pop_front();
            }
        } else {
            for (int i = cnt; i < 0; i++) {
                balloons.push_front(balloons.back());
                balloons.pop_back();
            }
        }
    }

    return 0;
}