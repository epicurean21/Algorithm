#include <iostream>

using namespace std;

int len, ans;
char map[8][8];

bool isOver(int x, int y) {
    if (x >= 0 && x < 8 && y >= 0 && y < 8) return false;
    return true;
}

bool isPalindrome(string str) {
    if (str.length() != len) return false;
    bool isTrue = true;
    int l = 0, r = len - 1;
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
        cin >> len;
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                cin >> map[i][j];

        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                string rcur = "", dcur = "";
                rcur += map[i][j];
                dcur += map[i][j];
                int rx = j, ry = i, dx = j, dy = i;
                bool possible1 = true, possible2 = true;
                for (int k = 1; k < len; k++) {
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
                }

                if (possible1)
                    if (isPalindrome(rcur))
                        ans++;
                if (possible2)
                    if (isPalindrome(dcur))
                        ans++;
            }
        }
        cout << "#" << tc << " " << ans << "\n";
    }
    return 0;
}