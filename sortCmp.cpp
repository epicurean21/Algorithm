// Baekjoon 10814
// sort + cmp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N;
vector<pair<int, pair<int, string>>> people;

// second.first 가 작은 순, 같다면 first가 작은 순
bool cmp(pair<int, pair<int, string>> a, pair<int, pair<int, string>> b) {
    if (a.second.first == b.second.first)
        return a.first < b.first;
    else
        return a.second.first < b.second.first;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N;
    people.resize(N);
    for (int i = 0; i < N; i++) {
        people[i].first = i;
        cin >> people[i].second.first >> people[i].second.second;
    }

    sort(people.begin(), people.end(), cmp);
    for (int i = 0; i < people.size(); i++)
        cout << people[i].second.first << " " << people[i].second.second << '\n';
    return 0;
}

/*
// pq를 활용해서 풀이 (min-heap, 순서대로 age, idx, name)
// 메모리를 많이 쓰지만 아주 조금 더 빠르다.
#include <iostream>
#include <queue>
using namespace std;

int N, age;
string str;
priority_queue<pair<int, pair<int, string>>, vector<pair<int, pair<int, string>>>, greater<pair<int, pair<int, string>>>> pq;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> age >> str;
        pq.push({age, {i, str}});
    }

    while(!pq.empty()) {
        cout << pq.top().first << " " << pq.top().second.second << '\n';
        pq.pop();
    }
    return 0;
}
 */