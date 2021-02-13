#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    srand((unsigned int) time(NULL));
    int num = rand() % 101;
    cout << num << '\n';
    return 0;
}