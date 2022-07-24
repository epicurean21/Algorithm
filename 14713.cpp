/**
 * 14713 앵무새
 * 자료구조, 문자열, 큐
 */
#include <iostream>
#include <queue>

using namespace std;
#define MAX 101
int N;
string message, tmp, L;
queue<string> parrot_messages[MAX];

bool check(string cur) {
    bool result = false;
    for (int i = 0; i < N; i++) {
        if (!parrot_messages[i].empty() && cur == parrot_messages[i].front()) {
            parrot_messages[i].pop();
            result = true;
            break;
        }
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    cin.ignore(MAX, '\n');
    for (int i = 0; i < N; i++) {
        tmp = "";
        getline(cin, message);
        for (char c: message) {
            if (c == ' ') {
                parrot_messages[i].push(tmp);
                tmp = "";
            } else
                tmp += c;
        }
        parrot_messages[i].push(tmp);
    }

    getline(cin, L);
    tmp = "";
    for (char i: L) {
        if (i == ' ') {
            if (!check(tmp)) {
                cout << "Impossible\n";
                return 0;
            }
            tmp = "";
        } else
            tmp += i;
    }
    if (check(tmp))
        cout << "Possible\n";
    else
        cout << "Impossible\n";
    return 0;
}