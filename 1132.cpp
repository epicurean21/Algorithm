#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;
#define ll long long
vector<pair<ll, int>> score(10);
int N, number[10];
string input[51];
bool impossible[10];

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
        for (int j = 0; j < length; j++)
            score[input[i][j] - 'A'].first += calculateScore(length - i - 1);
    }

    for (int i = 0; i < N; i++) {
        ll tmp = pow(10, input[i].length());
        for (int j = 0; j < input[i].length(); j++) {
            char cur = input[i][j];
            score[cur - 'A'].first += tmp;
            tmp /= 10;
        }
    }

    sort(score.begin(), score.end());
    int j = 0;
    for (int i = 0; i < 10; i++) {
        int cur = score[j++].second;
        number[cur] = i;
    }
    for (int i = 0; i < 10; i++) {
        if (impossible[score[i].second]) {
            for (int j = i + 1; j < 10; j++) {
                if (!impossible[score[j].second]) {
                    int from = score[i].second;
                    int to = score[j].second;
                    int tmp = number[from];
                    number[from] = number[to];
                    number[to] = tmp;
                }
            }
        }
    }
    ll ans = 0;
    for (int i = 0; i < N; i++) {
        int length = input[i].length();
        for (int j = 0; j < input[i].length(); j++) {
            int mul = pow(10, --length);
            ans += (ll) number[input[i][j] - 'A'] * mul;
        }
    }
    cout << ans << '\n';
    return 0;
}