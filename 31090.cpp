/**
 * 31090 2023은 무엇이 특별할까
 * 브론즈문제,, 쉬움
 */
#include "iostream"

using namespace std;
int t;
string n;

bool is_special_year(string year) {
    int last_two_number = (year[year.size() - 1] - '0') + (year[year.size() - 2] - '0') * 10;
    int input_year = stoi(year) + 1;

    if (input_year % last_two_number == 0) {
        return true;
    } else {
        return false;
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> t;
    while (t--) {
        cin >> n;
        if (is_special_year(n)) cout << "Good\n";
        else cout << "Bye\n";
    }

    return 0;
}