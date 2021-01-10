#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int N, K, weight, cnt;
bool flag;
vector<int> kit;
vector<int> order;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> K;
    kit.resize(N);
    order.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> kit[i];
        order[i] = i;
    }
    sort(order.begin(), order.end());
    do {
        weight = 500;
        flag = false;
        for(int i = 0; i < N; i++) {
            weight += kit[order[i]];
            weight -= K;
            if(weight < 500) {
                flag = true;
                break;
            }
        }
        if(!flag)
            cnt++;
    } while(next_permutation(order.begin(), order.end()));
    cout << cnt << "\n";
    return 0;
}