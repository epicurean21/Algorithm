#include <iostream>
#include <vector>
#include <map>

using namespace std;
#define alphabet 26
int C, N, Q;
string insert;
map<string, int> m;

class Trie {
private:
    Trie *next[alphabet];
    bool isFinished;

public:
    Trie() {
        fill(next, next + alphabet, nullptr);
        isFinished = false;
    }

    ~Trie() {
        for (int i = 0; i < alphabet; i++)
            if (next[i])
                delete next[i];
    }

    void insert(char *key) {
        if (*key == '\0') {
            isFinished = true;
            return;
        }

        int nextWord = *key - 'a';
        if (!next[nextWord])
            next[nextWord] = new Trie();
        next[nextWord]->insert(key + 1);
    }

    bool find(char *key) {
        if (*key == '\0')
            return false;

        if (this->isFinished)
            if (m.find(key) != m.end())
                return true;

        int nextWord = *key - 'a';
        if (next[nextWord] == nullptr)
            return false;
        return next[nextWord]->find(key + 1);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> C >> N;
    Trie *color_nickname = new Trie();

    for (int i = 0; i < C; i++) {
        cin >> insert;
        color_nickname->insert(&insert[0]);
    }

    for (int i = 0; i < N; i++) {
        cin >> insert;
        m[insert] = i;
    }

    cin >> Q;
    for (int i = 0; i < Q; i++) {
        cin >> insert;

        if (color_nickname->find(&insert[0]))
            cout << "Yes\n";
        else
            cout << "No\n";
    }

    return 0;
}
