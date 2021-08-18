#include <iostream>
#include <string>
#include <vector>

using namespace std;
#define alphabet 26
int C, N, Q;
vector<string> color;

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

    void insert(string key, int idx) {
        if (key[idx] == '\0') {
            isFinished = true;
            return;
        }

        if (!next[key[idx] - 'a'])
            next[key[idx] - 'a'] = new Trie();
        next[key[idx] - 'a']->insert(key, idx + 1);
    }

    bool find(string key, int idx) {
        if (key[idx] == '\0') {
            if (!this->isFinished)
                return false;
            return true;
        }

        int nextWord = key[idx] - 'a';
        if (next[nextWord] == nullptr)
            return false;
        return next[nextWord]->find(key, idx + 1);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> C >> N;
    Trie *color_nickname = new Trie();

    for (int i = 0; i < C; i++) {
        string insert;
        cin >> insert;
        color.emplace_back(insert);
    }

    for (int i = 0; i < N; i++) {
        string insert;
        cin >> insert;
        for (auto &j : color) {
            string input = j + insert;
            input += '\0';
            color_nickname->insert(input, 0);
        }
    }

    cin >> Q;
    for (int i = 0; i < Q; i++) {
        string teamName;
        cin >> teamName;

        if (color_nickname->find(teamName, 0))
            cout << "Yes\n";
        else
            cout << "No\n";
    }

    return 0;
}