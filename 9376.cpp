/**
 * 9376 탈옥
 * 그래프, DFS
 * 다익스트라
 * (. 빈공간, * 벽, # 문, $ 죄수)
 * 최소의 문을 열어서 탈출시켜야한다.
 * 한놈이 탈출했을 때, 해당 경로로 다른놈이 탈출 할 수 있는지 확인 ?
 * 단순 계산으론 안될듯..
 * 음 두 죄수가 만날 수 있는 점을 찾아서 밖으로 나가는 길의 최솟값
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;
#define MAX 101
int tc, h, w;
int dx[] = {1, 0, -1, 0}, dy[] = {0, 1, 0, -1};
bool chk[MAX][MAX];
vector<pair<int, int>> prisoners;
char map[MAX][MAX];

void init(int H, int W) {
    for (int i = 0; i <= H; i++)
        for (int j = 0; j <= W; j++)
            map[i][j] = ' ';
    prisoners.clear();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> tc;

    while (tc--) {
        cin >> h >> w;
        init(h, w);
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                cin >> map[i][j];
                if (map[i][j] == '$')
                    prisoners.emplace_back(j, i); // 죄수 x, y 좌표
            }
        }


    }
    return 0;
}