#include <iostream>
#include <cstring>
#include <vector>
#include <string>

using namespace std;
int M, W, N;
char map[4][4];
bool visited[4][4];
int score[] = {0, 0, 0, 1, 1, 2, 3, 5, 11};
int dy[] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dx[] = {-1, 0, 1, -1, 1, 1, 0, -1};
int Count = 0, sum = 0;
vector<char> sol;
string answer, s;

struct TrieNode {
    TrieNode *children[26];
    bool isEnd;
    bool isHit;

    TrieNode() {
        isEnd = false;
        for (int i = 0; i < 26; i++)
            children[i] = NULL;
    }

    TrieNode *getChild(char c) {
        return children[c - 'A'];
    }

    void clear() {
        isHit = false;
        for (int i = 0; i < 26; i++) {
            if (children[i] != NULL) {
                children[i]->clear();
            }
        }
    }

    bool hasChild(char c) {
        return children[c - 'A'] != NULL;
    }

};

struct Trie {
    TrieNode *root = new TrieNode();

    void insert(string word) {
        TrieNode *current = root;
        for (int i = 0; i < word.length(); i++) {
            char c = word[i];
            int index = c - 'A';
            if (current->hasChild(c) == false) {
                current->children[c - 'A'] = new TrieNode();
            }
            current = current->getChild(c);
        }
        current->isEnd = true;
    }

    bool checkWord(string word) {
        TrieNode *current = root;
        for (int i = 0; i < word.length(); i++) {
            char c = word[i];
            if (current->hasChild(c)) {
                current = current->getChild(c);
            } else {
                return false;
            }
        }
        return current->isEnd;
    }

};

bool cmp(string args0, string args1) {
    if (args1.size() == args0.size()) {
        int n = args0.compare(args1);
        if (n > 0)
            return true;
        else
            return false;
    } else
        return args0.size() < args1.size();
}

void dfs(int y, int x, int length, TrieNode *node) {
    visited[y][x] = true;
    sol.push_back(map[y][x]);

    if (node->isEnd == true && node->isHit == false) {
        node->isHit = true;
        sum += score[length];
        Count++;
        string foundWord = "";
        for (int i = 0; i < sol.size(); i++)
            foundWord += sol[i];

        if (cmp(answer, foundWord) > 0)
            answer = foundWord;
    }

    for (int i = 0; i < 8; i++) {
        int ty = y + dy[i];
        int tx = x + dx[i];
        if (0 <= ty && ty < 4 && 0 <= tx && tx < 4)
            if (visited[ty][tx] == false && node->hasChild(map[ty][tx]))
                dfs(ty, tx, length + 1, node->getChild(map[ty][tx]));
    }

    visited[y][x] = false;
    sol.erase(sol.begin() + length - 1);
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    Trie tr;
    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> s;
        tr.insert(s);
    }
    cin >> W;
    tr.root->clear();
    for (int k = 0; k < W; k++) {
        memset(map, 0, sizeof(map));
        memset(visited, false, sizeof(visited));
        answer = "";
        sum = 0;
        Count = 0;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                char a;
                cin >> a;
                map[i][j] = a;
            }
        }
        for (int y = 0; y < 4; y++)
            for (int x = 0; x < 4; x++)
                if (tr.root->hasChild(map[y][x]))
                    dfs(y, x, 1, tr.root->getChild(map[y][x]));
        tr.root->clear();
        cout << sum << " " << answer << " " << Count << "\n";
    }
    return 0;
}