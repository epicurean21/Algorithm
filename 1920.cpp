#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

vector<int> arr;
int N, M, X;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N;
    arr.resize(N);
    for (int i = 0; i < N; i++)
        cin >> arr[i];

    sort(arr.begin(), arr.end());
    cin >> M;
    for (int i = 0; i < M; i++) {
        cin >> X;

        int left = 0, right = N - 1;
        bool ans = false;
        while (left <= right) {
            int m = (left + right) / 2;
            if (X == arr[m]) {
                ans = true;
                break;
            } else if (X > arr[m])
                left = m + 1;
            else
                right = m - 1;
        }

        if (ans)
            cout << "1\n";
        else
            cout << "0\n";
    }
    return 0;
}