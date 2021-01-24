#include <iostream>
#include <string>
#include <cstring>
#include <stack>

using namespace std;
#define MAX 1002
string str1, str2;
int len1, len2;
int dp[MAX][MAX];
pair<int, int> tracking[MAX][MAX];
stack<char> ans;

int max(int a, int b) {
    return a > b ? a : b;
}

// p1, p2 까지의 것들 중에서 LCS (꼭 p1, p2를 포함 할 필요는 없음)
int calc(int p1, int p2) {
    if (p1 < 0 || p2 < 0)
        return 0;
    if (dp[p1][p2] != -1)
        return dp[p1][p2];
    // 문자가 같다면
    if (str1[p1] == str2[p2]) {
//        tracking[p1][p2].first = p1 - 1;
//        tracking[p1][p2].second = p2 - 1;
        return dp[p1][p2] = calc(p1 - 1, p2 - 1) + 1;
    }
        // 다르면
        /*
        int tmp1, tmp2;
        tmp1 = calc(p1 - 1, p2);
        tmp2 = calc(p1, p2 - 1);
        if (tmp1 > tmp2) {
            tracking[p1][p2].first = p1 - 1;
            tracking[p1][p2].second = p2;
            return dp[p1][p2] = tmp1;
        } else {
            tracking[p1][p2].first = p1;
            tracking[p1][p2].second = p2 - 1;
            return dp[p1][p2] = tmp2;
        }
         */
    else {
        return dp[p1][p2] = max(calc(p1, p2 - 1), calc(p1 - 1, p2));
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    memset(dp, -1, sizeof(dp));
    cin >> str1;
    cin >> str2;
    len1 = str1.length();
    len2 = str2.length();
    //cout << calc(len1 - 1, len2 - 1) << '\n';
    int max_length = 0;
    for (int i = 0; i < len1; i++) {
        for (int j = 0; j < len2; j++) {
            if (str1[i] == str2[j])
                dp[i][j] = dp[i - 1][j - 1] + 1;
            else {
                if (dp[i - 1][j] > dp[i][j - 1])
                    dp[i][j] = dp[i - 1][j];
                else
                    dp[i][j] = dp[i][j - 1];
            }
        }
    }
    cout << dp[len1 - 1][len2 - 1] << '\n';

    int i = str1.length() - 1;
    int j = str2.length() - 1;
    while (dp[i][j] != 0) {
        if (dp[i][j] == dp[i][j - 1])
            j--;
        else if (dp[i][j] == dp[i - 1][j])
            i--;
        else {
            ans.push(str1[i]);
            i--;
            j--;
        }
    }
    while (!ans.empty()) {
        cout << ans.top();
        ans.pop();
    }
    cout << '\n';
    return 0;
}
/*
#include <iostream>
#include <algorithm>
#include <string>

using namespace std;
#define MAX 1001
int d[MAX][MAX];
string temp1, temp2;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> temp1 >> temp2;

    string a, b;
    a = " " + temp1;
    b = " " + temp2;

    int na = a.size();
    int nb = b.size();

    for (int i = 1; i < na; i++) { // LCS 문자 길이 찾기
        for (int j = 1; j < nb; j++) {
            if (a[i] == b[j])
                d[i][j] = d[i - 1][j - 1] + 1;
            else
                d[i][j] = max(d[i][j - 1], d[i - 1][j]);
        }
    }
    cout << d[na - 1][nb - 1] << '\n';
    string ans;
    int i = na - 1;
    int j = nb - 1;

    while (d[i][j] != 0) {
        if (d[i][j] == d[i][j - 1])
            j--;
        else if (d[i][j] == d[i - 1][j])
            i--;
        else { //대각선이 1차이
            ans += a[i];
            i--;
            j--;
        }
    }
    reverse(ans.begin(), ans.end());
    cout << ans << "\n";
    return 0;
}
 */