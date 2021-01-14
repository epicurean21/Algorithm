#include <iostream>
#include <vector>

using namespace std;
#define MAX 200001
int H, N, sz;
vector<int> size(MAX);
vector<int> up;
vector<int> down;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> H;
    for (int i = 0; i < N / 2; i++) {
        cin >> sz;
        down.push_back(sz);
    }
    for (int i = N / 2; i < N; i++) {
        cin >> sz;
        up.push_back(sz);
    }


    return 0;
}