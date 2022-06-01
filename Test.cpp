#include <iostream>
#include <queue>
#include <map>

using namespace std;
int T, k, n;
char oper;
priority_queue<int> max_heap;
priority_queue<int, vector<int>, greater<>> min_heap;
map<int, int> m;

void init() {
    while (!max_heap.empty())
        max_heap.pop();
    while (!min_heap.empty())
        min_heap.pop();
    m.clear();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;
    while (T--) {
        init();
        cin >> k;
        while (k--) {
            cin >> oper;
            if (oper == 'I') {
                cin >> n;
                min_heap.push(n);
                max_heap.push(n);
                m[n]++;
            } else {
                cin >> n;
                if (n == -1) {
                    while (!min_heap.empty() && m[min_heap.top()] == 0)
                        min_heap.pop();
                    if (min_heap.empty()) continue;
                    m[min_heap.top()]--;
                    min_heap.pop();
                } else {
                    while (!max_heap.empty() && m[(max_heap.top())] == 0)
                        max_heap.pop();
                    if (max_heap.empty()) continue;
                    m[max_heap.top()]--;
                    max_heap.pop();
                }
            }
        }
        while (!max_heap.empty() && m[max_heap.top()] == 0) max_heap.pop();
        while (!min_heap.empty() && m[min_heap.top()] == 0) min_heap.pop();

        if (max_heap.empty() || min_heap.empty())
            cout << "EMPTY\n";
        else
            cout << max_heap.top() << " " << min_heap.top() << '\n';
    }

    return 0;
}