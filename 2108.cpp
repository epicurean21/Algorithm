/**
 * 2108 통계학
 * 수학, 출력
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int arr[8001], N, idx, max_val;
double sum;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> N;

    vector<int> list;
    for (int i = 0; i < N; i++) {
        int num;
        cin >> num;
        sum += num;
        if (num <= 0)
            idx = -num;
        else
            idx = 4000 + num;
        arr[idx]++;

        if (arr[idx] > max_val)
            max_val = arr[idx];
        list.push_back(num);
    }

    cout << fixed;
    cout.precision(0);
    if(sum / N == 0)
        cout << abs(sum / N) << '\n';
    else
        cout << sum / N << '\n';

    sort(list.begin(), list.end());
    cout << list[list.size() / 2] << '\n';

    bool flag = false;
    int result = 0;
    for (int i = -4000; i < 4001; i++) {
        if (i <= 0)
            idx = -i;
        else
            idx = 4000 + i;

        if (arr[idx] == max_val) {
            result = i;

            if (flag)
                break;
            flag = true;
        }
    }

    cout << result << '\n';
    cout << list[list.size() - 1] - list[0];

    return 0;
}