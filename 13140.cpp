#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int N, d, e, h, l, o, r, w, num[7], first, second;
vector<int> number = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
bool flag;

void solve() {
    do {
        for(int i = 0; i < 7; i++)
            num[i] = number[i];
        h = num[0];
        e = num[1];
        l = num[2];
        o = num[3];
        w = num[4];
        r = num[5];
        d = num[6];
        first = h * 10000 + e * 1000 + l * 110 + o;
        second = w * 10000 + o * 1000 + r * 100 + l * 10 + d;
        if(first + second == N && h != 0 && w != 0) {
            flag = true;
            break;
        }
    } while (next_permutation(number.begin(), number.end()));

    if(flag && N < 100000)
        cout << "  " << first << "\n+ " << second << "\n-------\n  " << N << "\n";
    else if(flag && N >= 100000)
        cout << "  " << first << "\n+ " << second << "\n-------\n " << N << "\n";
    else
        cout << "No Answer\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N;
    if (N > 199998)
        cout << "No Answer\n";
    else {
        solve();
    }
    return 0;
}