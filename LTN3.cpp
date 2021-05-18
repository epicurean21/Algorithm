#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
using namespace std;

struct compare {
    bool operator()(pair<int,int> a, pair<int,int> b) {
        if(b.second == a.second)
            return a.first < b.first;
        else
            return a.second < b.second;
    }
};

bool cmpVector(vector<int> a, vector<int> b) {
    if(a[0] == b[0])
        return a[1] > b[1];
    else
        return a[0] < b[0];
}

// min-heap이면서 손해비용 크고, 도착시간 빠른 순
priority_queue<pair<int,int>, vector<pair<int,int>>, compare> pq;
vector<vector<int>> ads = {{1,3},{3,2},{5,4}};
int solution() {
    int answer = 0;
    sort(ads.begin(), ads.end(), cmpVector);
    int i = 0, cur_time = 0;
    while (i < ads.size() || !pq.empty()) {

        if (i < ads.size() && cur_time >= ads[i][0]) {
            pq.push({ads[i][0], ads[i][1]});
            i++;
            continue;
        }

        if (!pq.empty()) {
            int cost = (cur_time - pq.top().first) * pq.top().second;
            cur_time += 5;
            answer += cost;
            pq.pop();
        } else
            cur_time = ads[i][0];
    }
    return answer;
}
int main() {
    cout << solution();
    return 0;
}
