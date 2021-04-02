#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int N, M, input, cnt;
vector<int> crane, box;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> input;
        crane.push_back(input);
    }
    cin >> M;
    for (int i = 0; i < M; i++) {
        cin >> input;
        box.push_back(input);
    }
    sort(crane.begin(), crane.end(), greater<int>());
    sort(box.begin(), box.end(), greater<int>());
    if (box[0] > crane[0]) {
        cout << "-1\n";
        return 0;
    }
    while (!box.empty()) {
        cnt++;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < box.size(); j++) {
                if (crane[i] >= box[j]) {
                    box.erase(box.begin() + j);
                    break;
                }
            }
        }
    }
    cout << cnt << "\n";
    return 0;
}