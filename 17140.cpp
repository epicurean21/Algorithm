/**
 * 17140 이차원 배열과 연산
 * 구현, 시뮬레이션, 삼성기출
 *
 * 어렵진않음. 쉬움, 근데 Row/Col & 행/열 개념이 계속 헷갈림...
 * 쉬움
 */
#include "iostream"
#include "vector"
#include "algorithm"

using namespace std;
#define MAX 101
int r, c, k, map[MAX][MAX], cnt, row, col, currentLength;

void calculateR() {
    int maxLength = 0;
    for (int i = 0; i < col; i++) {
        vector<pair<int, int>> calculateNumbers;
        vector<int> countNumbers(MAX);

        for (int j = 0; j < row; j++) countNumbers[map[i][j]]++;

        for (int j = 1; j < MAX; j++)
            if (countNumbers[j] != 0) calculateNumbers.emplace_back(countNumbers[j], j);
        sort(calculateNumbers.begin(), calculateNumbers.end());

        currentLength = 0;
        for (int j = 0; j < row; j++) map[i][j] = 0;
        for (int j = 0; j < calculateNumbers.size(); j++) {
            map[i][currentLength++] = calculateNumbers[j].second;
            map[i][currentLength++] = calculateNumbers[j].first;
        }

        maxLength = max(maxLength, currentLength);
    }
    row = maxLength;
}

void calculateC() {
    int maxLength = 0;
    for (int i = 0; i < row; i++) {
        vector<pair<int, int>> calculateNumbers;
        vector<int> countNumbers(MAX);

        for (int j = 0; j < col; j++) countNumbers[map[j][i]]++;

        for (int j = 1; j < MAX; j++)
            if (countNumbers[j] != 0) calculateNumbers.emplace_back(countNumbers[j], j);
        sort(calculateNumbers.begin(), calculateNumbers.end());

        currentLength = 0;
        for (int j = 0; j < col; j++) map[j][i] = 0;
        for (int j = 0; j < calculateNumbers.size(); j++) {
            map[currentLength++][i] = calculateNumbers[j].second;
            map[currentLength++][i] = calculateNumbers[j].first;
        }

        maxLength = max(maxLength, currentLength);
    }
    col = maxLength;
}

void init() {
    r--;
    c--;
    col = row = 3;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> c >> r >> k;
    init();

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            cin >> map[i][j];

    while (map[c][r] != k && ++cnt <= 100) {
        if (col >= row) calculateR();
        else calculateC();
    }

    if (map[c][r] != k || 100 < cnt) cout << "-1\n";
    else cout << cnt << '\n';

    return 0;
}