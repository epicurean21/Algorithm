/**
 * 2174 로봇 시뮬레이션
 * 구현, 시뮬레이션
 */

#include <iostream>
#include <map>

using namespace std;
#define MAX 101

int X, Y, N, M, x, y, land[MAX][MAX], j, iter, dx[] = {0, 1, 0, -1}, dy[] = {1, 0, -1, 0};
char direction;
map<int, pair<pair<int, int>, int>> robots;
string error_message;
bool flag = true;

int rotate(char dir, int cur_dir) {
    if (dir == 'L') {
        cur_dir--;
        if (cur_dir < 0)
            return 3;
        else
            return cur_dir;
    } else if (dir == 'R')
        return ((cur_dir + 1) % 4);
    else
        return -1;
}

pair<pair<int, int>, bool> move(int robot_num, int xx, int yy, int cur_dir, int times) {
    land[yy][xx] = 0;
    for (int i = 0; i < times; i++) {
        int nx = xx + dx[cur_dir];
        int ny = yy + dy[cur_dir];

        if (nx < 1 || nx > X || ny < 1 || ny > Y) {
            error_message = "Robot " + to_string(robot_num) + " crashes into the wall\n";
            return {{nx, ny}, false};
        }
        if (land[ny][nx]) {
            error_message = "Robot " + to_string(robot_num) + " crashes into robot " + to_string(land[ny][nx]) + "\n";
            return {{nx, ny}, false};
        }

        xx = nx;
        yy = ny;
    }
    land[yy][xx] = robot_num;
    return {{xx, yy}, true};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> X >> Y >> N >> M;
    for (int i = 1; i <= N; i++) {
        cin >> x >> y >> direction;
        land[y][x] = i;
        switch (direction) {
            case 'N':
                robots.insert({i, {{x, y}, 0}});
                break;
            case 'E':
                robots.insert({i, {{x, y}, 1}});
                break;
            case 'S':
                robots.insert({i, {{x, y}, 2}});
                break;
            case 'W':
                robots.insert({i, {{x, y}, 3}});
                break;
            default:
                break;
        }
    }

    while (M-- && flag) {
        cin >> j >> direction >> iter;
        auto robot = robots.find(j);
        int cur_dir = robot->second.second;
        int cur_x = robot->second.first.first;
        int cur_y = robot->second.first.second;
        robots.erase(j);

        if (direction == 'L' || direction == 'R') {
            for (int i = 0; i < iter; i++)
                cur_dir = rotate(direction, cur_dir);
        } else if (direction == 'F') {
            pair<pair<int, int>, bool> next = move(j, robot->second.first.first, robot->second.first.second, cur_dir,
                                                   iter);
            flag = next.second;
            cur_x = next.first.first;
            cur_y = next.first.second;
        }

        if (flag)
            robots.insert({j, {{cur_x, cur_y}, cur_dir}});
    }

    if (flag)
        cout << "OK\n";
    else
        cout << error_message;

    return 0;
}