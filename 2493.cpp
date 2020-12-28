#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int N;
stack<pair<int, int>> tower;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N;
    for (int i = 0; i < N; i++) {
        int height;
        cin >> height;
        while (!tower.empty() && height > tower.top().second)
            tower.pop();

        if (tower.empty())
            cout << "0 ";
        else
            cout << tower.top().first << " ";

        tower.push({i + 1, height});
    }

    return 0;
}