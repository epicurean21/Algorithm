/**
 * 24891: 단어 마방진
 * 백트래킹, 완전탐색
 */
#include <iostream>
#include <vector>

using namespace std;
#define MAX 20
int L, N;
string word;
bool visited[MAX];
vector<string> words, candidate;

bool isMagicalMap() {
    for (int i = 0; i < L; i++) {
        for (int j = 0; j < L; j++)
            if (candidate[i][j] != candidate[j][i]) return false;
    }
    return true;
}

void printMagicalMap() {
    for (int i = 0; i < L; i++)
        cout << candidate[i] << "\n";
}

void backTracking(int cnt) {
    if (cnt == L) {
        if (isMagicalMap()) {
            printMagicalMap();
            exit(0);
        }
        return;
    }

    for (int i = 0; i < N; i++) {
        if (visited[i]) continue;
        visited[i] = true;
        candidate.emplace_back(words[i]);
        backTracking(cnt + 1);
        visited[i] = false;
        candidate.pop_back();
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> L >> N;
    for (int i = 0; i < N; i++) {
        cin >> word;
        words.emplace_back(word);
    }

    sort(words.begin(), words.end());
    backTracking(0);
    cout << "NONE\n";
    return 0;
}