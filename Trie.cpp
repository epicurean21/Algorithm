#include <iostream>
#include <string>
#include <cstring>
// 14425번 문자열 집합
using namespace std;
#define alphabet 26
#define MAX 501
int N, M, ans;

class Trie {
private:
    Trie *next[alphabet];
    bool finished;

public:
    Trie() {
        //memset(this->next, NULL, sizeof(this->next));
        fill(next, next + alphabet, nullptr);
        finished = false;
    }

    ~Trie() {
        for (int i = 0; i < alphabet; i++) {
            if (next[i])
                delete next[i];
        }
    }

    void insert(char *key) {
        if (*key == '\0') { // 문자열 마지막이라면 이 부분이 끝임을 알리자 finished = true
            finished = true;
            return;
        }

        int nextIdx = *key - 'a'; // 문자를 숫자로, alphabet 26개 배열[26] 중 한개로
        if (!next[nextIdx]) // 그게 아직 없다면 생성
            next[nextIdx] = new Trie();
        next[nextIdx]->insert(key + 1); // 있다면 다음 글자로
    }

    bool find(char *key) { // 찾기
        if (*key == '\0') { // 끝이라면
            if (!this->finished)
                return false;
            return true;
        }// 다 찾았으니 true
        //if (this->finished) // 끝까지 왔는데 안끝났으면 false
        //return false;
        int nextIdx = *key - 'a';
        if (next[nextIdx] == nullptr)
            return false;
        return next[nextIdx]->find(key + 1);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N >> M;
    Trie *root = new Trie();
    for (int i = 0; i < N; i++) {
        char str[MAX];
        cin >> str;
        root->insert(str);
    }

    for (int i = 0; i < M; i++) {
        char str[MAX];
        cin >> str;
        if (root->find(str))
            ans++;
    }
    cout << ans << '\n';
    return 0;
}
/*
#include <iostream>
#include <map>
#include <string>

using namespace std;
int N, M;
map<string, int> m;
string str;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int ans = 0;
    cin >> N >> M;
    for (int i = 0; i < N; i++) {
        cin >> str;
        m.insert({str, i});
    }
    for (int i = 0; i < M; i++) {
        cin >> str;
        if (m.count(str) == 1)
            ans++;
    }
    cout << ans << '\n';
    return 0;
}*/
