#include <iostream>
#include <vector>
using namespace std;
#define MAX 101

int N, x, y, d, g, ans;
int map[MAX][MAX];
int dx[] = {1, 0, -1, 0};
int dy[] = {0, -1, 0, 1};
int squareX[] = {1, 1, 0};
int suqareY[] = {0, 1, 1};
pair<int, int> zero_generation(int x, int y, int d) {
    return {x + dx[d], y + dy[d]};
}

void count_square() {
    for(int i = 0; i < 100; i++) {
        for(int j = 0; j < 100; j++) {
            if(map[j][i] && map[j + suqareY[0]][i + squareX[0]] &&
               map[j + suqareY[1]][i + squareX[1]] && map[j + suqareY[2]][i + squareX[2]])
                ans++;
        }
    }
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N;
    for (int i = 0; i < N; i++) {
        vector<int> direction;
        cin >> x >> y >> d >> g;
        map[y][x] = 1;
        pair<int, int> next;
        next = zero_generation(x, y, d);
        map[next.second][next.first] = 1;
        int lastx = next.first;
        int lasty = next.second;
        direction.push_back(d);
        for (int k = 0; k < g; k++) {
            for(int i = direction.size() - 1; i >= 0; i--) {
                int cd = direction[i];
                int nd = (cd + 1) % 4;
                int nx = lastx + dx[nd];
                int ny = lasty + dy[nd];
                if(0 <= nx && nx <= 100 && 0 <= ny && ny <= 100)
                    map[ny][nx] = true;
                direction.push_back(nd);
                lastx = nx;
                lasty = ny;
            }
        }
    }

    count_square();
    cout << ans << "\n";
    return 0;
}