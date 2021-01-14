#include <iostream>
#include <cstring>

using namespace std;
#define MAX 10001
int T,N;
char phone[MAX][11];
class Trie {
private:
    bool isEnd;
    Trie *next[10];

public:
    Trie() {
        memset(next, 0, sizeof(next));
        isEnd = false;
    }

    ~Trie() {
        for (int i = 0; i < 10; i++)
            if (next[i])
                delete next[i];
    }

    void insert(char *key) {
        if (*key == '\0') {
            isEnd = true;
        } else {
            int idx = *key - '0';
            if (next[idx] == 0)
                next[idx] = new Trie();
            next[idx]->insert(key + 1);
        }
    }

    bool find(char* key) {
        if(*key == '\0')
            return true;
        if(isEnd)
            return false;
        int idx = *key - '0';
        return next[idx]->find(key + 1);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> T;
    while(T--) {
        cin >> N;
        Trie* root = new Trie();
        for(int i = 0; i < N; i++) {
            cin >> phone[i];
            root->insert(phone[i]);
        }

        bool flag = true;
        for(int i = 0; i< N; i++) {
            if(!root->find(phone[i])) {
                flag = false;
                break;
            }
        }
        delete root;
        if(flag)
            cout << "YES\n";
        else
            cout << "NO\n";
    }
    return 0;
}