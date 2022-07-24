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

int numLength(int num) {
    if (!num) return 1;

    int result = 0;
    while (num) {
        num /= 10;
        result++;
    }
    return result;
}

bool isPossible(int num) { // 고장난 버튼이있는지 확인하는 메소드
    if (num == 0) {
        if (find(button.begin(), button.end(), 0) == button.end()) // 일치하는 원소가 없다면
            return true;
        else
            return false;
    }

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
    int calc = 0;

    for (int i = 0; i < MAX; i++) {
        if (isPossible(i)) { // 누룰 수 있는 버튼인지 확인
            int click = abs(N - i); // 클릭 값 (채널 이동 횟수)
            if (result > click) {
                result = click; // result는 결국 + - 로 이동해야하는 횟수이다.
                calc = i; // 이동 채널 값
            }
        }
    }

    int a = result + numLength(calc); // 숫자 크기만큼 버튼을 눌러야하니, 길이를 구한다
    int b = abs(N - 100); // 100번부터 단순 움직이는 경우
    cout << min(a, b) << "\n";

    return 0;
}