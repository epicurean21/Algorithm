/**
 * 16212: 정열적인 정렬
 * 정렬문제..?
 */
#include <iostream>
#include <algorithm>

using namespace std;
#define MAX 500001
int N, a[MAX];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    for (int i = 0; i < N; i++)
        cin >> a[i];
    sort(a, a + N);
    for (int i = 0; i < N; i++)
        cout << a[i] << " ";
    return 0;
}