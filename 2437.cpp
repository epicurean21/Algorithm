#include <iostream>
#include <algorithm>

using namespace std;
#define ll long long
#define MAX 1001
int N, chu[MAX], sum[MAX];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    for (int i = 1; i <= N; i++)
        cin >> chu[i];
    sort(chu, chu + N + 1);
    for (int i = 1; i <= N; i++)
        sum[i] = chu[i] + sum[i - 1]; // 누적 합 구해놓기

    if (chu[1] > 1)
        cout << "1\n";
    else {
        for (int i = 1; i <= N; i++) {
            if (chu[i] > sum[i - 1] + 1) {
                cout << sum[i - 1] + 1 << '\n';
                return 0;
            }
        }
        cout << sum[N] + 1 << '\n';
    }
    return 0;
}