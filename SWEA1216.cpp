#include <iostream>

using namespace std;

int test_case, ans;
char map[101][101];

int max(int a, int b) {
    return a > b ? a : b;
}

bool isOver(int x, int y) {
    if (x >= 0 && x < 100 && y >= 0 && y < 100) return false;
    return true;
}

bool isPalindrome(string str) {
    bool isTrue = true;
    int l = 0, r = str.length() - 1;
    while (l <= r) {
        if (str[l] != str[r]) {
            isTrue = false;
            break;
        } else {
            l++;
            r--;
        }
    }

    return isTrue;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    for (int tc = 1; tc <= 10; tc++) {
        ans = 0;
        cin >> test_case;
        for (int i = 0; i < 100; i++)
            for (int j = 0; j < 100; j++)
                cin >> map[i][j];

        for (int i = 0; i < 100; i++) {
            for (int j = 0; j < 100; j++) {
                string rcur = "", dcur = "";
                rcur += map[i][j];
                dcur += map[i][j];
                int rx = j, ry = i, dx = j, dy = i;
                bool possible1 = true, possible2 = true;
                for (int k = 1; k < 100; k++) {
                    rx++;
                    dy++;
                    if (isOver(rx, ry))
                        possible1 = false;
                    else
                        rcur += map[ry][rx];

                    if (isOver(dx, dy))
                        possible2 = false;
                    else
                        dcur += map[dy][dx];
                    if (possible1)
                        if (isPalindrome(rcur))
                            ans = max(ans, rcur.length());
                    if (possible2)
                        if (isPalindrome(dcur))
                            ans = max(ans, dcur.length());
                }
            }
        }
        cout << "#" << tc << " " << ans << "\n";
    }
    return 0;
}