#include <iostream>
#include <string>

using namespace std;
#define MAX 1001
int N, Q, cnt;
char S[MAX][101];

class Trie {
private:
    Trie *next[26];
    bool finished;
public:
    Trie() {
        for (int i = 0; i < 26; i++)
            next[i] = nullptr;
        finished = false;
    }

    ~Trie() {
        for (int i = 0; i < 26; i++)
            if (next[i])
                delete next[i];
    }

    void insert(char *k) {
        if (*k == '\0')
            return;
        int nextIdx = *k - 'a';
        if (!next[nextIdx])
            next[nextIdx] = new Trie();
        next[nextIdx]->insert(k + 1);
    }

    void query(char *s, char *k) {
        if (*k == '\0' || *s == '\0')
            return;

        int nextS = *s - 'a';
        int nextIdx = *k - 'a';
        if (!next[nextIdx])
            next[nextS]->query(s + 1, k);
        else {
            cnt++;
            next[nextIdx]->query(s + 1, k + 1);
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    for (int i = 0; i < N; i++)
        cin >> S[i];
    cin >> Q;
    for (int i = 0; i < Q; i++) {
        bool flag = false;
        Trie *root = new Trie();

        char str[10001];
        cin >> str;
        root->insert(str);
        for (int j = 0; j < N; j++) {
            cnt = 0;
            root->query(str, S[j]);
            int length = 0;
            for (int k = 0; k < 101; k++) {
                if (S[j][k] != '\0')
                    length++;
                else
                    break;
            }
            if(length == cnt)
                flag= true;
        }
        if(flag)
            cout << "YES\n";
        else
            cout << "NO\n";
        delete root;
    }
    return 0;
}
/*
3
woo
www
jun
3
myungwoo
hongjun
dooho
 */