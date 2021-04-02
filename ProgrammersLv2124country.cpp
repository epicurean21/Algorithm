#include <iostream>
#include <string>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    string answer = "";
    int a = 0;
    while (n != 0) {
        a = n % 3;
        n /= 3;
        if (a == 0) {
            answer = '4' + answer;
            n -= 1;
        } else if (a == 1)
            answer = '1' + answer;
        else if (a == 2)
            answer = '2' + answer;
    }
    cout << answer << '\n';
    return 0;
}