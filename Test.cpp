#include <iostream>
#include <vector>

using namespace std;
#define MAX 102
int T, N;
char X;
int Failure_Function[MAX];
string P, tmp;

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

int KMP(int n, int m) {
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

    return matching_index.size();
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
        calculate_failure_function(N);

        int length = 0;
        for (int i = 0; i < N; i++) {
            tmp += P[i];
            length = max(length, KMP(tmp.length(), P.length()));
        }

        cout << length << "\n";
    }

    return 0;
}