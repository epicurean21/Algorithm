#include <iostream>
#include <algorithm>

using namespace std;
#define MAX 101
int T, N, scores[MAX];

int main() {
    cin >> T;

    for (int t = 1; t <= T; t++) {
        cin >> N;
        for (int i = 0; i < N; i++)
            cin >> scores[i];

        sort(scores, scores + N);

        bool possibleScores[10001] = {false,};
        possibleScores[0] = true;

        int max = 0;
        for (int i = 0; i < N; i++) {
            max += scores[i];
            for (int k = max; k >= 0; k--)
                if (possibleScores[k])
                    possibleScores[k + scores[i]] = true;
        }

        int cnt = 0;
        for (int i = 0; i <= max; i++)
            if (possibleScores[i])
                cnt++;
        cout << '#' << t << ' ' << cnt << '\n';
    }
    return 0;
}
/*
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// DFS로 모든 경우를 탐색하면 시간 초과
// DP로 푼다.
// 이전에 등장했던 가능한 값에서 + 시켜 새로운 값을 확인하는 방식
// bool형 배열을 이용하여 값의 등장 유무 확인
int main() {
    int T;
    cin >> T;

    for (int t = 1; t <= T; t++) {
        vector<int> scores;
        int N;
        cin >> N;

        scores.resize(N);
        for (int i = 0; i < N; i++)
            cin >> scores[i];

        // 계산의 편의를 위해 낮은 순으로 정렬
        sort(scores.begin(), scores.end());

        // N의 최대 크기가 100, 최대 점수도 100이므로 가능한 최대 점수는 10000
        bool possibleScores[10001] = { false, };

        // 0은 항상 가능한 점수이므로
        possibleScores[0] = true;

        int max = 0;
        for (int i = 0; i < N; i++) {
            max += scores[i];

            // max부터 시작한다. 점수가 3일 경우 0에서 0+3=3이 체크되면, 3에서 3+3=6의 엉뚱한 점수를 체크한다.
            for (int k = max; k >= 0; k--)
                if (possibleScores[k])
                    possibleScores[k + scores[i]] = true;
        }

        int cnt = 0;
        for (int i = 0; i <= max; i++)
            if (possibleScores[i])
                cnt++;

        cout << '#' << t << ' ' << cnt << '\n';
    }

    return 0;
}
 */
