/**
 * leetcode #13
 * Roman to Integer
 * Difficulty: EASY
 * -
 * translate roman numerals to an integer
 */
#include "iostream"
#include "stack"

using namespace std;
int romanNumerals[26];

void init() {
    romanNumerals['I' - 'A'] = 1;
    romanNumerals['V' - 'A'] = 5;
    romanNumerals['X' - 'A'] = 10;
    romanNumerals['L' - 'A'] = 50;
    romanNumerals['C' - 'A'] = 100;
    romanNumerals['D' - 'A'] = 500;
    romanNumerals['M' - 'A'] = 1000;
}

int getRomanCombinationNumber(string roman) {
    if (roman == "IV") return 4;
    else if (roman == "IX") return 9;
    else if (roman == "XL") return 40;
    else if (roman == "XC") return 90;
    else if (roman == "CD") return 400;
    else if (roman == "CM") return 900;
    else return 0;
}

int romanToInt(string s) {
    int calculatedNumber = 0;
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == 'I' || s[i] == 'X' || s[i] == 'C') {
            string combinationString;
            combinationString += s[i];
            if (i != s.length()) combinationString += s[i + 1];

            int romanCombinationNumber = getRomanCombinationNumber(combinationString);
            if (romanCombinationNumber) {
                calculatedNumber += romanCombinationNumber;
                i++;
            } else calculatedNumber += romanNumerals[s[i] - 'A'];
        } else calculatedNumber += romanNumerals[s[i] - 'A'];
    }

    return calculatedNumber;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    init();
    string s;
    while (cin >> s) {
        if (s == "0") exit(1);
        cout << romanToInt(s) << '\n';
    }

    return 0;
}