#include <iostream>
#include <queue>

using namespace std;

int N, num;
priority_queue<int, vector<int>, greater<int>> maxPq; // 반대로 내림차순
priority_queue<int> minPq; // 반대로 오름차순 우리는 중앙값을 찾아야하니 !

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> num;
        if (minPq.size() == maxPq.size())
            minPq.push(num);
        else
            maxPq.push(num);

        if(!minPq.empty() && !maxPq.empty()) {
            if(minPq.top() > maxPq.top()) {
                int tmp = maxPq.top();
                maxPq.push(minPq.top());
                minPq.pop();
                minPq.push(tmp);
                maxPq.pop();
            }
        }
        cout << minPq.top() << "\n";
    }
    return 0;
}