#include <iostream>
#include <algorithm>

using namespace std;
#define MAX 10001
int T, N, score[101];
bool chk[MAX];

void init() {
    chk[0] = true;
    for (int i = 1; i < MAX; i++)
        chk[i] = false;
}

int cnt() {
    int tmp = 0;
    for (int i = 0; i < MAX; i++)
        if (chk[i])
            tmp++;
    return tmp;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> T;
    for (int t = 1; t <= T; t++) {
        init();
        cin >> N;
        int tmp = 0;
        for (int i = 0; i < N; i++) {
            cin >> score[i];
            chk[score[i]] = true;
            tmp += score[i];
        }
        chk[tmp] = true;
        for (int i = 2; i < N; i++) {
            do {
                cout << "#" << i << '\n';
                tmp = 0;
                for (int j = 0; j < i; j++) {
                    cout << score[j] << " ";
                    tmp += score[j];
                }
                cout << '\n';
                chk[tmp] = true;
            } while (next_permutation(score, score + N));
        }

        cout << cnt() << '\n';
    }
    return 0;
}
/*
1
4
1 2 3 4
 */