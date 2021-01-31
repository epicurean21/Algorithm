#include <iostream>

using namespace std;
#define MAX 201
int N, K, color[21], cnt[MAX], bulb[MAX]; // index, color


int countBulb(int clr) { // clr가 연속으로 몇개 켜져있는지.
    int tmp = 0;
    int ret = 0;
    for (int i = 1; i <= N; i++) {
        if (clr == bulb[i]) {
            tmp++;
            ret = max(ret, tmp);
        } else
            tmp = 0;
    }
    return ret;
}

int countClr() { // 현재 켜져있는 색상이 몇종류인지
    bool chk[MAX] = {false,};
    int tmp = 0;
    for (int i = 1; i <= N; i++) {
        if (chk[bulb[i]] != 1) {
            chk[bulb[i]] = 1;
            tmp++;
        }
    }
    return tmp;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    return 0;
}