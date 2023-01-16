/*
 * 11000 강의실 배정
 * 정렬, 그리디 알고리즘
 *
 * 강의 시작 시간으로 정렬한 뒤,
 * 순회하면서 다음 강의의 시작 시간이 현재 pq (종료시간 빠른 순)의 탑 보다 크거나 같다면 pq에 넣지 않는다. (넣고 pop)
 * 그 다음 pq 에 남은 강의 개수가 총 필요한 강의실 수가 된다.
 */
#include "iostream"
#include "vector"
#include "queue"
#include "algorithm"

using namespace std;
int n;
vector<pair<int, int>> classes;

bool cmp(pair<int, int> a, pair<int, int> b) {
    if (a.first == b.first) return a.second < b.second;
    else return a.first < b.first;
}

priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;


int main() {
    cin.tie(nullptr)->ios::sync_with_stdio(false);

    cin >> n;
    classes.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> classes[i].first >> classes[i].second;
    }

    sort(classes.begin(), classes.end(), cmp);

    pq.push({classes[0].second, classes[0].first});

    for (int i = 1; i < n; i++) {
        int cur_start = classes[i].first;
        int cur_end = classes[i].second;

        pq.push({cur_end, cur_start});

        if (pq.top().first <= cur_start)
            pq.pop();
    }

    cout << pq.size() << '\n';

    return 0;
}