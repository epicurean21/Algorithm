#include <iostream>
#include <vector>
#include <cstring>

using namespace std;
#define MAX 1001
#define INF 987654321
int W, H, G, X, Y, E, dist[32][32];
bool thumb[32][32], hole[32][32], flag;
int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};

struct point {
    int sx, sy, x, y, t, v;

    point(int sx, int sy, int x, int y, int t, int v) : sx(sx), sy(sy), x(x), y(y), t(t), v(v) {}

    point() {}
};

point map[MAX][MAX];
vector<point> edge;

void init() {
    flag = false;
    memset(hole, 0, sizeof(hole));
    memset(thumb, 0, sizeof(thumb));
    memset(map, 0, sizeof(map));
}

void buildMap() {
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (i == H - 1 && j == W - 1) continue;
            if (thumb[i][j]) continue;
            if (map[i][j].v == 1) {
                edge.push_back(map[i][j]);
                continue;
            }
            for (int k = 0; k < 4; k++) {
                int nx = j + dx[k];
                int ny = i + dy[k];
                if (nx < 0 || nx >= W || ny < 0 || ny >= H) continue;
                edge.push_back(point(j, i, nx, ny, 1, 0));
            }
        }
    }
}

void bellman() {
    dist[0][0] = 0;
    for (int i = 1; i <= W * H; i++) {
        int cnt = 0;
        for (point cur : edge) {
            int sx = cur.sx, sy = cur.sy, ex = cur.x, ey = cur.y, t = cur.t, v = cur.v;
            if (dist[sy][sx] == INF) continue;
            if (dist[ey][ex] > dist[sy][sx] + t) {
                dist[ey][ex] = dist[sy][sx] + t;
                cnt++;
            }
        }

        if (i == W * H - 1) {
            if (cnt)
                cout << "Never\n";
            else if (dist[H - 1][W - 1] == INF)
                cout << "Impossible\n";
            else
                cout << dist[H - 1][W - 1] << '\n';
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    while (1) {
        cin >> W >> H;
        if (W == 0 && H == 0) break;
        init();
        cin >> G;
        for (int i = 0; i < G; i++) { // 묘비
            cin >> X >> Y;
            thumb[Y][X] = true;
        }
        cin >> E;
        for (int i = 0; i < E; i++) {
            int X1, Y1, X2, Y2, T;
            cin >> X1 >> Y1 >> X2 >> Y2 >> T;
            hole[Y1][X1] = true;
            map[Y1][X1] = point(X1, Y1, X2, Y2, T, 1);
        }

        buildMap();
        bellman();
    }
    return 0;
}