#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int max(int a, int b) {
    return a > b ? a : b;
}

bool cmp(string a, string b) {
    int length = a.length();
    length = max(length, b.length());
    char aa = '0';
    char bb = '0';
    for (int i = 0; i < length; i++) { // 긴 놈으로
        if (a.length() > i)
            aa = a[i];
        else
            aa = '0';
        if (b.length() > i)
            bb = b[i];
        else
            bb = '0';

        if (aa - '0' > bb - '0')
            return true;

        if (aa - '0' < bb - '0')
            return false;
    }

    if (a.length() == 1 && b.length() > 1) {
        if (b[1] == '0')
            return true;
        else
            return false;
    }
    if (a.length() > 1 && b.length() == 1) {
        if (a[1] == '0')
            return false;
        else
            return true;
    }
}

vector<int> numbers = {3, 30};

string solution() {
    string answer = "";
    vector<string> tmp;
    for (int i = 0; i < numbers.size(); i++)
        tmp.push_back(to_string(numbers[i]));
    sort(tmp.begin(), tmp.end(), cmp);
    for (int i = 0; i < tmp.size(); i++) {
        cout << tmp[i] << " ";
        answer += tmp[i];
    }
    return answer;
}

int main() {
    cout << solution() << '\n';
}