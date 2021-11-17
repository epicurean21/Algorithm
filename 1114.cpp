/**
 * 1114: 통나무 자르기
 * 이분탐색, 그리디 알고리즘
 * 결정문제 패턴?
 * "길이가 L인 통나무의 적절한 위치를 선택해 C번 잘라 각각 통나무의 최대길이가 최소가 되게하자."
 * 를 "길이가 L인 통나무를 C번잘랐을때, 나온 통나무들의 길이를 length이하가 되게할수있는가?" 로 바꿔서 풀자
 *
 * 통나무의 최소길이 = 1, 통나무의 최대길이 = L
 * length = (통나무의 최소길이 + 통나무의 최대길이) / 2;
 * 방법으로 이분탐색을 하자
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int L, K, C, cut;
vector<int> cutable;

int get_lenth() {
    int l = 1, r = L;
    while (l < r) {
        int m = (l + r) / 2;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> L >> K >> C; // L 10억

    for (int i = 0; i < K; i++) {
        cin >> cut;
        cutable.emplace_back(cut);
    }

    sort(cutable.begin(), cutable.end());


    return 0;
}