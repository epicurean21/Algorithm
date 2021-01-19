#include <iostream>

using namespace std;
#define MAX 120
bool flag[MAX + 1];

void Eratos() {
    for (int i = 2; i <= MAX; i++) {
        if (!flag[i]) {
            cout << i << ", \n";
            for (int j = i + i; j <= MAX; j += i)
                flag[j] = true;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    Eratos();
    return 0;
}