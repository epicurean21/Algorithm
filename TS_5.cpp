#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;


bool desc(int a, int b) {
    return a > b;
}

vector<int> solution(vector<int> fruitWeights, int k) {
    vector<int> answer;
    map<int, int> m;

    int idx = 0;
    /**
     * N개의 과일 중 연속된 K개 과일 ?
     * 그 선택된 K개 중 가장 무거운 과일의 무게가 점수
     */

    for (int i = 0; i < fruitWeights.size() - k + 1; i++) {
        int score = 0;
        for (int j = i; j < i + k; j++) {
            score = max(score, fruitWeights[j]);
        }
        if (m.count(score)) continue;
        else {
            m.insert({score, idx++});
            answer.emplace_back(score);
        }
    }

    sort(answer.begin(), answer.end(), desc);

    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    vector<int> fruitWeights;
    fruitWeights.emplace_back(30);
    fruitWeights.emplace_back(40);
    fruitWeights.emplace_back(10);
    fruitWeights.emplace_back(20);
    fruitWeights.emplace_back(30);
    int k = 3;

    vector<int> sol = solution(fruitWeights, k);
    for (int i = 0; i < sol.size(); i++)
        cout << sol[i] << " ";
    return 0;
}