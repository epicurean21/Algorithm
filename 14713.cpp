/**
 * 14713 앵무새
 * 자료구조, 문자열, 큐
 */
#include <iostream>
#include <queue>

using namespace std;
#define MAX 101
int N;
vector<string> S;
queue<string> words[MAX], L;
string message, tmp;

bool isPossible() {
    while (!L.empty()) {
        string cur = L.front();
        L.pop();
        bool result = false;
        for (int i = 0; i < N; i++) {
            if (!words[i].empty() && cur == words[i].front()) {
                words[i].pop();
                result = true;
            }
        }
        if (!result)
            return false;
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    getline(cin, message);
    for (int i = 0; i < N; i++) {
        getline(cin, message);
        S.emplace_back(message);
    }

    int idx = 0;
    for (string s: S) {
        for (char c: s) {
            if (c == ' ') {
                words[idx].push(tmp);
                tmp = "";
            } else
                tmp += c;
        }

        words[idx++].push(tmp);
        tmp = "";
    }

    getline(cin, message); // L 입력받기
    for (char c: message) {
        if (c == ' ') {
            L.push(tmp);
            tmp = "";
        } else
            tmp += c;
    }
    L.push(tmp);

    if (isPossible())
        cout << "Possible\n";
    else
        cout << "Impossible\n";


    return 0;
}