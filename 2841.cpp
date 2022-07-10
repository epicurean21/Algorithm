/**
 * 2841 외게인의 기타 연주
 * stack, 구현
 */
#include <iostream>
#include <vector>
#include <stack>

using namespace std;
int N, P, l, n, ans;
vector<stack<int>> notes(6);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N >> P;
    for (int i = 0; i < N; i++) {
        cin >> l >> n;
        if (!notes[l - 1].empty() && notes[l - 1].top() > n) {
            while (!notes[l - 1].empty() && notes[l - 1].top() > n) {
                notes[l - 1].pop();
                ans++;
            }
        }
        if (notes[l - 1].empty() || notes[l - 1].top() < n) {
            ans++;
            notes[l - 1].push(n);
        }
    }
    cout << ans << "\n";
    return 0;
}