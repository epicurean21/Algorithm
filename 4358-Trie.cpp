#include <iostream>
#include <string>
#include <algorithm>

using namespace std;
#define TrieSize  128
int treeCnt;
char tree[35];

class Trie {
private:
    Trie *nextNode[TrieSize];
    int cnt;
public:
    Trie() { // 생성자
        fill(nextNode, nextNode + TrieSize, nullptr);
        cnt = 0;
    }

    ~Trie() {
        for (int i = 0; i < TrieSize; i++)
            delete nextNode[i];
    }

    void insert(char *key) {
        if (*key == '\0') {
            cnt++;
            treeCnt++;
            return;
        }

        int next = *key;

        if (nextNode[next] == nullptr)
            nextNode[next] = new Trie;

        nextNode[next]->insert(key + 1);
    }

    void printTree(int idx) {
        if (cnt > 0) {
            tree[idx] = '\0';
            cout << tree << " " << 100 * cnt / (double)treeCnt << "\n";
        }
        for (int next = 0; next < TrieSize; next++) {
            if (nextNode[next]) {
                tree[idx] = next;
                nextNode[next]->printTree(idx + 1);
            }
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cout << fixed;
    cout.precision(4);
    Trie *root = new Trie;

    while (cin.getline(tree, 35)) {
        root->insert(tree);
    }

    root->printTree(0);
    return 0;
}