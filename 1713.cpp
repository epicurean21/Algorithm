#include <iostream>

using namespace std;

int N, K, recommend[101], when[101], homany;

int main() {
    ios_base::sync_with_stdio(false);
    cout.tie(NULL);
    cin.tie(NULL);

    cin >> N >> K;
    for (int i = 1; i <= K; ++i) {
        int student;
        cin >> student;
        if (recommend[student] > 0) recommend[student]++;
        else {
            if (homany < N) {
                recommend[student]++;
                when[student] = i;
                homany++;
            } else {
                int change;
                int reco = 1111;
                for (int i = 1; i <= 100; ++i) {
                    if (!recommend[i]) continue;

                    if (reco > recommend[i]) {
                        change = i;
                        reco = recommend[i];
                    } else if (reco == recommend[i])
                        if (when[i] < when[change]) change = i;

                }
                recommend[student]++;
                when[student] = i;
                recommend[change] = 0;
                when[change] = 0;
            }
        }
    }
    for (int i = 1; i <= 100; ++i)
        if (when[i])
            cout << i << " ";

    return 0;
}