/*
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
#define ll long long
vector<pair<ll, int>> score(10);
int N;
string input[51];
bool chk[10];

ll calculateScore(int length) {
    ll tmp = 1;
    while (length--)
        tmp *= 10;
    return tmp;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;

    for (int i = 0; i < 10; i++)
        score[i].second = i;
    for (int i = 0; i < N; i++) {
        cin >> input[i];
        int length = input[i].length();
        for (int j = 0; j < length; j++) {
            score[input[i][j] - 'A'].first += calculateScore(length - j - 1);
        }
    }

    sort(score.begin(), score.end());
    reverse(score.begin(), score.end());

    ll ans = 0;

    for (int i = 9; i >= 0; i--) {
        for (int j = 0; j < 10; j++) {
            if (score[j].first != 0 && !chk[j]) {
                chk[j] = true;
                ans += ((ll) i * score[j].first);
                break;
            }
        }
    }
    cout << ans << "\n";
    return 0;
}*/

#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;
#define ll long long
#define MAX 13
ll use[10], d, ans;
bool check[10];
int n, z;
char num[MAX];

int main() {
    ios::sync_with_stdio(false);
    cout.tie(NULL);

    cin >> n;
    for (int i = 0; i < n; i++) {
        d = 1;
        cin >> num;
        check[num[0] - 'A'] = true;
        for (int j = strlen(num) - 1; j >= 0; j--) {
            use[num[j] - 'A'] += d;
            d *= 10;
        }
    }
    for (int i = 0; i < 10; i++) {
        if (!check[i]) {
            z = i;
            break;
        }
    }
    for (int i = 0; i < 10; i++)
        if (!check[i] && use[i] < use[z])
            z = i;

    use[z] = 0;
    sort(use, use + 10);
    reverse(use, use + 10);
    for (int i = 0; i < 10; i++)
        ans += (9 - i) * use[i];

    cout << ans << '\n';
    return 0;
}
