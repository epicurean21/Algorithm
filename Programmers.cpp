#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;
vector<int> times = {7, 10};
int n = 6;

long long solution() {
    int max_num = 0;
    for (int i = 0; i < times.size(); i++)
        max_num = max(max_num, times[i]);

    long long left = 0, right = max_num * n;
    long long answer = right;
    while (left <= right) {
        long long m = (left + right) / 2;
        long long sum = 0;
        for (int k : times) {
            if (k > m)
                break;
            sum += m / k;
        }

        if (sum >= n) {
            right = m - 1;
            answer = min(answer, m);
        } else if (sum < n) {
            left = m + 1;
        }
    }
    return answer;
}

int main() {
    cout << solution() << '\n';
}