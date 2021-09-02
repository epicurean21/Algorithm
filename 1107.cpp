/**
* 리모컨
 * 브루트포스 알고리즘으로 해결
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;
#define INF 9999999
#define MAX 1000001

int N, M, tmp;
vector<int> button;

int min(int a, int b) {
    return a > b ? b : a;
}

int length(int num) {
    int result = 0;
    while (num) {
        num /= 10;
        result++;
    }
    return result;
}

bool isPossible(int num) {
    if (num == 0)
        if (find(button.begin(), button.end(), 0) == button.end())
            return true;
        else
            return false;

    while (num) {
        if (find(button.begin(), button.end(), num % 10) != button.end())
            return false;
        num /= 10;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;

    for (int i = 0; i < M; i++) {
        cin >> tmp;
        button.emplace_back(tmp);
    }

    int result = INF;
    int similar = 0;

    for (int i = 0; i < MAX; i++) {
        if (isPossible(i)) { // 고장 안난 버튼
            int click = abs(N - i);
            if (result > click) {
                result = click;
                similar = i;
            }
        }
    }

    int a = result + length(similar);
    int b = abs(N - 100);
    cout << min(a, b) << "\n";
    return 0;
}