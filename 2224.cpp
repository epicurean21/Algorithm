#include <iostream>
#include <queue>
#include <string>

using namespace std;
#define ALPHA 123
#define INF 99
int N;
int alpha[ALPHA][ALPHA];
priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

void reset() {
    for (int i = 0; i < ALPHA; i++) {
        for (int j = 0; j < ALPHA; j++) {
            if (i == j) continue;
            alpha[i][j] = INF;
        }
    }
}

void cal() {
    for (int i = 0; i < ALPHA; i++)
        for (int j = 0; j < ALPHA; j++)
            if (alpha[i][j] != 0 && alpha[i][j] != INF)
                pq.push({i, j});
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N;
    reset();
    for (int i = 0; i < N; i++) {
        char A, B;
        string str;
        cin >> A >> str >> B;
        if(A == B) continue;
        int a = (int) (A - 'A');
        int b = (int) (B - 'A');
        alpha[a][b] = 1;
    }

    for (int k = 0; k < ALPHA; k++)
        for (int i = 0; i < ALPHA; i++)
            for (int j = 0; j < ALPHA; j++)
                if (alpha[i][j] > alpha[i][k] + alpha[k][j])
                    alpha[i][j] = alpha[i][k] + alpha[k][j];

    cal();
    cout << pq.size() << "\n";
    while (!pq.empty()) {
        char A = (char) (pq.top().first + 'A');
        char B = (char) (pq.top().second + 'A');
        pq.pop();
        cout << A << " => " << B << "\n";
    }
    return 0;
}