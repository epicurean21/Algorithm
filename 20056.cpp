/**
 * 20056: 마법사 상어와 파이어볼
 * 삼성 S/W 검정 시험
 */
#include <iostream>
#include <vector>

using namespace std;
#define MAX 52
int num, fb, k, result = 0;
int dx[] = {0, 1, 1, 1, 0, -1, -1, -1}, dy[] = {-1, -1, 0, 1, 1, 1, 0, -1};

struct fireball {
    int x, y, m, d, s;
};
vector<fireball> fire, dup;
fireball tmp;

int rtnPos(int a) {
    while (a < 1 || a > num) {
        if (a < 1) a += num;
        else a -= num;
    }
    return a;
}

void spell() {
    vector<int> arr[MAX][MAX];

    for (int i = 0; i < fire.size(); i++) {
        int cx = fire[i].x;
        int cy = fire[i].y;
        int cd = fire[i].d;
        int cs = fire[i].s;
        int nx = cx + dx[cd] * cs;
        int ny = cy + dy[cd] * cs;
        fire[i].x = rtnPos(nx);
        fire[i].y = rtnPos(ny);
        arr[fire[i].y][fire[i].x].push_back(i);
    }

    dup.clear();
    for (int i = 1; i <= num; i++) {
        for (int j = 1; j <= num; j++) {
            int len = arr[i][j].size();
            if (len > 1) {
                int sm = 0, ss = 0;
                bool allOdd = true, allEven = true;
                for (int t = 0; t < len; t++) {
                    sm += fire[arr[i][j][t]].m;
                    ss += fire[arr[i][j][t]].s;
                    if (fire[arr[i][j][t]].d % 2 == 0) allOdd = false;
                    if (fire[arr[i][j][t]].d % 2 == 1) allEven = false;
                }
                sm /= 5;
                if (sm) {
                    ss /= len;
                    int t = 1;
                    if (allEven || allOdd) t = 0;
                    tmp.x = fire[arr[i][j][0]].x;
                    tmp.y = fire[arr[i][j][0]].y;
                    tmp.s = ss;
                    tmp.m = sm;
                    for (; t < 8; t += 2) {
                        tmp.d = t;
                        dup.push_back(tmp);
                    }
                }
            } else if (len == 1) {
                tmp.x = fire[arr[i][j][0]].x;
                tmp.y = fire[arr[i][j][0]].y;
                tmp.m = fire[arr[i][j][0]].m;
                tmp.d = fire[arr[i][j][0]].d;
                tmp.s = fire[arr[i][j][0]].s;
                dup.push_back(tmp);
            }
        }
    }
    fire = dup;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> num >> fb >> k;
    int r, c, m, s, d;
    for (int i = 0; i < fb; i++) {
        cin >> r >> c >> m >> s >> d;
        tmp.x = c;
        tmp.y = r;
        tmp.m = m;
        tmp.d = d;
        tmp.s = s;
        fire.push_back(tmp);
    }
    while (k--) {
        spell();
    }
    for (int i = 0; i < fire.size(); i++)
        result += fire[i].m;
    cout << result;
    return 0;
}