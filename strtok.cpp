#include <iostream>
#include <cstring>
#include <vector>
#include <string>

using namespace std;

int sz;
char words[] = "The Curious Case of Benjamin Button";
char opers[] = "2 - 3 + 1 - 4 + 9 = 100";

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    char *ptr = strtok(words, " ");
    while (ptr != NULL) {
        cout << ptr << '\n';
        ptr = strtok(NULL, " "); // null부터 다시 자르기
    }

    ptr = strtok(opers, "+-= ");
    while (ptr != NULL) {
        cout << ptr << '\n';
        ptr = strtok(NULL, "=+/- ");
    }
    return 0;
}