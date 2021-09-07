/**
 * 9376 탈옥
 * 그래프, DFS
 * 다익스트라
 */

#include <iostream>

using namespace std;
#define MAX 101
int tc, h, w;
char map[MAX][MAX];

void init(int H, int W) {
    for (int i = 0; i <= H; i++)
        for (int j = 0; j <= W; j++)
            map[i][j] = ' ';

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tc;

    while (tc--) {
        cin >> h >> w;
        init(h, w);
        for (int i = 0; i < h; i++)
            for (int j = 0; j < w; j++)
                cin >> map[i][j];


    }
    return 0;
}