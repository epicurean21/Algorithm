/**
 * 16987 계란으로 계란치기
 * 브루트포스, 백트레킹, 구현
 */
#include "iostream"
#include "vector"

using namespace std;

int n, s, w, ans, cnt;
vector<pair<int, int>> eggs;

void breakTheEgg(int eggIdx) {
    if (eggIdx > n) return;
    for (int i = 0; i < n; i++) {
        if (eggs[eggIdx].first <= 0) breakTheEgg(eggIdx + 1);
        else if (eggs[i].first <= 0 || i == eggIdx) continue;
        else {
            eggs[eggIdx].first -= eggs[i].second;
            eggs[i].first -= eggs[eggIdx].second;
            breakTheEgg(eggIdx + 1);
            eggs[eggIdx].first += eggs[i].second;
            eggs[i].first += eggs[eggIdx].second;
        }
    }
    for (int i = 0; i < n; i++) if (eggs[i].first <= 0) cnt++;
    ans = max(ans, cnt);
    cnt = 0;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> s >> w;
        eggs.emplace_back(s, w);
    }

    breakTheEgg(0);
    cout << ans << '\n';
    return 0;
}