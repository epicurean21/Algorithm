#include <iostream>

using namespace std;
#define ll long long
ll tmp, S;
int N;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> S;
    int i = 1;
    while (1) {
        tmp += i;
        N++;
        if (tmp > S) {
            N--;
            break;
        }
        i++;
    }
    cout << N << '\n';
    return 0;
}