#include <iostream>
#include <string>
#include <cstring>
#include <vector>

using namespace std;
#define MAX 31
int w, b;
int score[] = {0, 0, 0, 1, 1, 2, 3, 5, 11};
int dx[] = {1, 1, 0, -1, -1, -1, 0, 1};
int dy[] = {0, 1, 1, 1, 0, -1, -1, -1};
char map[MAX][4][4]; // 순서대로 boggle 보드, i , j;
bool chk[4][4];
vector<char> sol;

class Trie {
private:
    Trie *next[26];
public:
    Trie() {
        fill(next, next + 26, nullptr);
    }

    ~Trie() {
        for (int i = 0; i < 26; i++)
            if (next[i])
                delete next[i];
    }

    void insert(char *k) {
        if (*k == '\0')
            return;

        int nextIdx = *k - 'A';
        if (!next[nextIdx])
            next[nextIdx] = new Trie();
        next[nextIdx]->insert(k + 1);
    }

    bool find(char *k) {
        if (*k == '\0')
            return true;
        int idx = *k - 'A';
        if (!next[idx])
            return false;
        return next[idx]->find(k + 1);
    }
};

Trie *Boggle = new Trie();

void dfs(int boggle, int x, int y, int length) {
    chk[y][x] = true;
    sol.push_back(map[boggle][y][x]);

    if (Boggle->find(k) == false)
        return;
    else

        for (int i = 0; i < 8; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx < 0 || nx >= 4 || ny < 0 || ny >= 4) continue;
            if (!chk[ny][nx]) {
                dfs(boggle, nx, ny, length + 1);
            }
        }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> w;
    for (int i = 0; i < w; i++) {
        char k[9];
        cin >> k;
        Boggle->insert(k);
    }
    cin >> b;
    for (int B = 1; B <= b; B++) {
        for (int i = 0; i < 4; i++) {
            string str;
            cin >> str;
            for (int j = 0; j < str.length(); j++)
                map[B][i][j] = str[j];
        }
    }

    for (int i = 1; i <= b; i++) {
        for (int y = 0; y < 4; y++) {
            for (int x = 0; x < 4; x++) {
                memset(chk, false, sizeof(chk));
                dfs(i, x, y, 1);
            }
        }
    }

    return 0;
}