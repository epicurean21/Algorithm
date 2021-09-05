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
#include <algorithm>
#include <vector>

using namespace std;

int N, x, y, cur_min = INT32_MAX, cur_max, ans;
vector<pair<int, int>> input;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;

    for (int i = 0; i < N; i++) {
        cin >> x >> y;
        input.emplace_back(x, y);
    }

    sort(input.begin(), input.end());

    for (int i = 0; i < input.size(); i++) {
        x = input[i].first;
        y = input[i].second;

        if (i == 0) { // 첫 번째
            ans += y - x;
            cur_min = x;
            cur_max = y;
            continue;
        }

        if (cur_max < x || cur_min > y) { // case 1 : 선분과 안겹침
            ans += (y - x);

            cur_max = max(y, cur_max);
            cur_min = min(x, cur_min);
            continue;
        }

        if (cur_min <= x && cur_max >= y) { // case 2 : 기존에 포함됨 무시
            continue;
        }

        if (cur_min <= x && cur_max <= y) { // case 3 : 일부만 겹침
            ans += (y - cur_max);
            cur_max = y;
        }
    }

    cout << ans << '\n';

    return 0;
}