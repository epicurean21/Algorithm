#include <iostream>
#include <vector>
#include <string>
/**
 * 카카오 인턴십 2021
 * 2번 거리두기 확인하기
 */
using namespace std;

int dx[] = {2, 1, 1, 0, 0, -1, -2, -1, -1, 0, 0, 1}, dy[] = {0, 0, 1, 1, 2, 1, 0, 0, -1, -1, -2, -1};

int hamming_distance(int x, int nx, int y, int ny) {
    return abs(x - nx) + abs(y - ny);
}

vector<int> solution(vector<vector<string>> places) {
    vector<int> answer;

    for (int i = 0; i < 5; i++) { // 각 대기실
        bool flag = false;

        for (int j = 0; j < 5; j++) { // 각 열
            for (int k = 0; k < 5; k++) {
                if (places[i][j][k] == 'P') { // 응시자

                    for (int d = 0; d < 12; d++) {
                        int nx = k + dx[d];
                        int ny = j + dy[d];

                        if (nx < 0 || nx >= 5 || ny < 0 || ny >= 5) continue;

                        if (places[i][ny][nx] == 'P') {
                            if (hamming_distance(k, nx, j, ny) == 1) {
                                flag = true;
                                break;
                            } else {
                                int mx = (nx + k) / 2;
                                int my = (ny + j) / 2;


                                if (k == nx || j == ny) {
                                    if (places[i][my][mx] == 'X') continue;
                                    flag = true;
                                }

                                if (places[i][ny][k] == 'X' && places[i][j][nx] == 'X') continue;
                                flag = true;
                            }
                        }
                    }
                    if (flag) break;
                }
                if (flag) break;
            }
            if (flag) break;
        }

        if (flag)
            answer.emplace_back(0);
        else
            answer.emplace_back(1);

    }
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    vector<vector<string>> places(5);
    for (int i = 0; i < 5; i++) {
        places[i].resize(5);
        for (int j = 0; j < 5; j++) {
            cin >> places[i][j];
        }
    }

    vector<int> answer = solution(places);
    for (int i = 0; i < answer.size(); i++)
        cout << answer[i] << " ";
    return 0;
}
/**
POOOP
OXXOX
OPXPX
OOXOX
POXXP
POOPX
OXPXP
PXXXO
OXXXO
OOOPP
PXOPX
OXOXP
OXPOX
OXXOP
PXPOX
OOOXX
XOOOX
OOOXX
OXOOX
OOOOO
PXPXP
XPXPX
PXPXP
XPXPX
PXPXP
*/