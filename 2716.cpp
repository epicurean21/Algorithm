#include <iostream>
#include <string>

using namespace std;
int N;

int Max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N;
    cin.ignore();
    while (N--) {
        string str;
        int cnt = 0, height = 0;
        getline(cin, str);
        if(str.size() != 0) {
            for (int i = 0; i < str.length(); i++) {
                if (str[i] == '[') {
                    cnt++;
                    height = Max(height, cnt);
                } else
                    cnt--;
            }
        }
        cout << (1 << height) << "\n";
    }
    return 0;
}