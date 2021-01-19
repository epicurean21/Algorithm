#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

#define INF 2000000001
using namespace std;
int N, Z = INF;
vector<int> liquor;

bool min(int a, int b) {
    int aa = abs(a);
    int bb = abs(b);
    return aa > bb ? true : false;
}

bool negative(int a) {
    return a < 0 ? true : false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    for (int i = 0; i < N; i++) {
        int tmp;
        cin >> tmp;
        liquor.push_back(tmp);
    }
    sort(liquor.begin(), liquor.end());
    if (liquor.size() == 2) {
        cout << liquor[0] << " " << liquor[1] << "\n";
        return 0;
    }

    int pointer1 = 0, pointer2 = liquor.size() - 1;
    int ans1 = 0, ans2 = liquor.size() - 1;
    while (pointer1 < pointer2) {
        int cal = liquor[pointer1] + liquor[pointer2];
        if(negative(cal)) { // 음수다
            if(min(Z, cal)) {
                Z = cal;
                ans1 = pointer1;
                ans2 = pointer2;
            }
            pointer1++;
        }
        else {
            if(min(Z, cal)) {
                Z = cal;
                ans1 = pointer1;
                ans2 = pointer2;
            }
            pointer2--;
        }
    }
    cout << liquor[ans1] << " " << liquor[ans2] << "\n";
    return 0;
}