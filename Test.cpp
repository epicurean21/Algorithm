#include "iostream"
#include "vector"
#include "algorithm"

using namespace std;
#define MAX 201
#define ROW resizeableArray.size()
#define COLUMN resizeableArray[0].size()
int r, c, k, a[3][3], cnt;
vector<vector<int>> resizeableArray(3);

void printValues(vector<pair<int, int>> input) {
    for (int i = 0; i < input.size(); i++)
        cout << "#" << i << " completed= value:" << input[i].first << ", count:" << input[i].second << "\n";
}

void printArray(vector<vector<int>> input) {
    cout << "------------------------\n";
    for (int i = 0; i < input.size(); i++) {
        for (int j = 0; j < input[i].size(); j++) {
            cout << input[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "------------------------\n";
}

int max(int x, int y) {
    return x <= y ? y : x;
}

bool sorting(pair<int, int> inputA, pair<int, int> inputB) {
    return inputA.second < inputB.second || inputA.second == inputB.second && inputA.first < inputB.first;
}

vector<vector<int>> calculateR(vector<vector<int>> input) {
    vector<vector<int>> newArray;
    int size = 0;
    for (int i = 0; i < input.size(); i++) {
        newArray.emplace_back();
        int numberCount[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        for (int j: input[i]) {
            numberCount[j]++;
        }
        vector<pair<int, int>> orderingNumbers;
        for (int j = 1; j <= 9; j++)
            if (numberCount[j] != 0) orderingNumbers.emplace_back(j, numberCount[j]);

        sort(orderingNumbers.begin(), orderingNumbers.end(), sorting);
        for (auto &orderingNumber: orderingNumbers) {
            newArray[i].emplace_back(orderingNumber.first);
            newArray[i].emplace_back(orderingNumber.second);
        }
        size = max(size, newArray[i].size());
    }

    for (auto &i: newArray) {
        if (i.size() == size) continue;
        int curSize = i.size();
        for (int j = 0; j < (size - curSize); j++) {
            i.emplace_back(0);
        }
    }

    return newArray;
}

vector<vector<int>> calculateC(vector<vector<int>> input) {
    vector<vector<int>> newArray;
    //for(int i = 0; i < input[0].size(); i++) newArray.emplace_back();

    int size = 0;
    for (int i = 0; i < input[0].size(); i++) {
        int numberCount[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        for (auto &j: input) {
            numberCount[j[i]]++;
        }
        vector<pair<int, int>> orderingNumbers;
        for (int j = 1; j <= 9; j++)
            if (numberCount[j] != 0) orderingNumbers.emplace_back(j, numberCount[j]);
        sort(orderingNumbers.begin(), orderingNumbers.end(), sorting);


        size = max(size, newArray.size());
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    for (int i = 0; i < 3; i++) resizeableArray[i].resize(3);
    cin >> r >> c >> k;
    r--;
    c--;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> a[i][j];
            resizeableArray[i][j] = a[i][j];
        }
    }

    while (resizeableArray[c][r] != k && ++cnt <= 100) {
        if (ROW >= COLUMN) {
            printArray(resizeableArray);
            resizeableArray = calculateR(resizeableArray);
            printArray(resizeableArray);
        } else {
            resizeableArray = calculateC(resizeableArray);
        }
    }

    if (resizeableArray[c][r] != k || 100 < cnt) cout << "-1\n";
    else cout << cnt << '\n';

    return 0;
}