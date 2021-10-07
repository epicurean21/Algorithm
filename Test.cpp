#include <iostream>
#include <vector>

using namespace std;
#define MAX 102
int T, N;
char X;
int Failure_Function[MAX];
string P, tmp; // Text, Pattern

void calculate_failure_function(int n) {
    Failure_Function[0] = 0; // Failure Function 0 은 항상 0
    int i = 1, j = 0;
    while (i < n) {
        if (P[i] == P[j]) { // Match !
            Failure_Function[i] = ++j; // F[i] = j + 1;
            i++; // i++;
        } else if (j > 0) { // j > 0 인데 mismatch인 경우, 즉 앞에서 몇 문자는 Match했음.
            j = Failure_Function[j - 1];
        } else { // mismatch 이면서, j = 0, Brute Force와 같이 첫 문자부터 틀렸기에 한 칸 shift
            Failure_Function[j] = 0;
            i++;
        }
    }
}

vector<int> KMP(int n, int m) {
    int i = 0, j = 0;
    vector<int> matching_index;

    while (i < n) {
        if (tmp[i] == P[j]) {
            if (j == m - 1) {
                matching_index.emplace_back(i - j);
                j = 0;
                continue;
            }
        } else if (j > 0)
            j = Failure_Function[j - 1];
        else
            i++;
    }

    return matching_index;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> T;
    while (T--) {
        cin >> N;
        P = "";
        tmp = "";
        for (int i = 0; i < N; i++) {
            cin >> X;
            P += X;
        }

        int length = 0;
        vector<int> ans;
        for (int i = 0; i < N; i++) {
            tmp += P[i];
            calculate_failure_function(tmp.length());
            vector<int> kmp_answer = KMP(P.length(), tmp.length());
            if (kmp_answer.size() > length)
                ans = kmp_answer;
        }

        for (auto i : ans)
            cout << i << " ";
        cout << "\n";
    }

    return 0;
}

/**
4
10
5 2 1 5 5 2 1 5 5 2
10
1 2 3 4 5 6 7 1 2 3
10
1 2 3 4 5 6 7 1 2 2
15
1 2 1 2 1 2 1 2 1 2 1 2 1 2 1
*/