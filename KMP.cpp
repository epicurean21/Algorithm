/*
 * KMP, 문자열 탐색에서 Brute Force 알고리즘으로 탐색하면, 문자비교간의 mismatch 발생시
 * 한 칸을 shift해서 계속해서 탐색을 이어나간다.
 * KMP 알고리즘은, 보다 효율적으로 진행하기 위해 'Failure Function'을 이용하여,
 * 앞에서 match가 진행됐던 애들을 고려하여 몇 칸을 뛸지를 결정한다.
 * 입력 Text의 길이 N, 비교 문자열 Pattern의 길이가 M이라면, O(M + N)의 Optimal 수행능력을 보인다.
 * Failure Function은, M의 길이를 같은 배열, F[M]으로 표현될 수 있다.
 * F[j] 는 Pattern의 j까지의 Prefix의 proper prefix와 proper suffix의 match길이의 최댓값이다.
 */

// 백준 1786 문제 [찾기]
#include <iostream>
#include <string>
#include <vector>

using namespace std;
#define MAX 101
string T, P;
int Failure_Function[MAX];

// Preprocessing ! 즉, Failure Function을 초기화한다.
void Calculate_Failure_Function(int M) {
    Failure_Function[0] = 0; // Failure Function 0 은 항상 0
    int i = 1, j = 0;
    while (i < M) {
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

vector<int> KMP(int N, int M) {
    int i = 0, j = 0; // i는 Text의 index, j는 Pattern의 index
    vector<int> matching_index;

    while (i < N) {
        if (T[i] == P[j]) { // match !
            if (j == M - 1) { // 즉, 문자열 전체 발견 !
                matching_index.emplace_back(i - j); // 발견 된 위치의 시작 인덱스 !
                j = 0;
                continue;
            }
            i++;
            j++;
        } else if (j > 0) { // mismatch, 앞에서 최소 몇개는 만났음
            j = Failure_Function[j - 1];
        } else {
            i++;
        }
    }

    return matching_index;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    getline(cin, T);
    getline(cin, P);

    Calculate_Failure_Function(P.length());

    vector<int> KMP_answer = KMP(T.length(), P.length());

    cout << KMP_answer.size() << "\n";
    for (int i = 0; i < KMP_answer.size(); i++)
        cout << KMP_answer[i] + 1 << " ";
    cout << '\n';

    return 0;
}