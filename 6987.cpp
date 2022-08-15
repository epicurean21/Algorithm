/**
 * 6987 월드컵
 * 백트래킹, 브루트포스
 */
#include <iostream>

using namespace std;
#define TEAM 6
#define GROUP 4
#define RESULT 3
int map[GROUP][TEAM][RESULT], ans[GROUP], win_cnt, draw_cnt, lost_cnt, game_cnt;
bool suspicious;

void init() {
    suspicious = false;
    win_cnt = draw_cnt = lost_cnt = 0;
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    for (int i = 0; i < GROUP; i++) {
        init();
        for (int j = 0; j < TEAM; j++) {
            game_cnt = 0;
            for (int k = 0; k < RESULT; k++) {
                cin >> map[i][j][k];
                game_cnt += map[i][j][k];

                if (k == 0)
                    win_cnt += map[i][j][k];
                else if (k == 1) {
                    if (draw_cnt > 0)
                        draw_cnt -= map[i][j][k];
                    else
                        draw_cnt += map[i][j][k];
                } else
                    lost_cnt += map[i][j][k];
            }
            if (game_cnt != TEAM - 1)
                suspicious = true;
        }

        cout << "\ngroup " << i << " ,  " << "win_cnt: " << win_cnt << " draw_cnt: " << draw_cnt << " lost_cnt: "
             << lost_cnt << '\n';
        if (win_cnt != lost_cnt || draw_cnt != 0 || suspicious)
            ans[i] = 0;
        else
            ans[i] = 1;
    }
    for (int i = 0; i < GROUP; i++)
        cout << ans[i] << " ";
    cout << '\n';

    return 0;
}

/*
5 0 0 3 0 2 2 0 3 0 0 5 4 0 1 1 0 4
4 1 0 3 0 2 4 1 0 1 1 3 0 0 5 1 1 3
5 0 0 4 0 1 2 2 1 2 0 3 1 0 4 0 0 5
3 1 1 1 0 4 1 1 3 3 0 2 3 0 2 3 0 2
*/