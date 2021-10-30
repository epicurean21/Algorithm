/**
 * 1114: 통나무 자르기
 * 이분탐색, 그리디 알고리즘
 */
#include <iostream>
#include <vector>

using namespace std;
int L, K, C, cut;
vector<int> cutable;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> L >> K >> C; // L 10억

    for (int i = 0; i < K; i++) {
        cin >> cut;
        cutable.emplace_back(cut);
    }

    return 0;
}