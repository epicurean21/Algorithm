/**
 * 2812 크게 만들기
 * 스택, 자료구조, 덱
 */
#include "iostream"
#include "deque"

using namespace std;

int n, k, cnt;
string input;
deque<char> dq;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> k;
    cin >> input;

    int i;
    for (i = 0; i < input.length(); i++) {
        if (cnt == k) break;
        while (!dq.empty() && dq.back() - '0' < input[i] - '0' && cnt < k) {
            dq.pop_back();
            cnt++;
        }
        dq.push_back(input[i]);
    }

    for (; i < input.length(); i++) dq.push_back(input[i]);
    while (cnt < k) {
        dq.pop_back();
        cnt++;
    }

    while (!dq.empty()) {
        cout << dq.front();
        dq.pop_front();
        cnt++;
    }
    cout << '\n';

    return 0;
}