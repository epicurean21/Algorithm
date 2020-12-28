#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
#define MAX 101
int N, M, K;
int map[MAX][MAX];
bool been[MAX][MAX];
int sz, cnt;

int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};

vector<int> area;
void dfs(int x, int y) {
    been[y][x] = true;
    int curx = x;
    int cury = y;
    sz++;
    for(int i = 0; i < 4; i++) {
        int nx = curx + dx[i];
        int ny = cury + dy[i];
        if(0 <= nx && 0 <= ny && nx < N && ny < M && !been[ny][nx] && !map[ny][nx]) {
            dfs(nx, ny);
        }
    }
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    cin >> M >> N >> K; // y , x , k
    for(int i = 0; i < K; i++) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        for(int x = x1; x < x2; x++) {
            for(int y = y1; y< y2; y++) {
                map[y][x] = 1;
            }
        }
    }

    for(int i =0; i < M; i++) {
        for(int j = 0; j< N; j++) {
            if(map[i][j] != 0) continue;
            if(been[i][j]) continue;
            sz = 0;
            dfs(j, i);
            area.push_back(sz);
        }
    }
    sort(area.begin(), area.end());
    cout << area.size() << "\n";
    for(int i = 0; i <area.size(); i++)
        cout << area[i] << " ";
    cout << "\n";

    return 0;
}