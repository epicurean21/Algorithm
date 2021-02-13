#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>

using namespace std;
#define MAX 100001
int N, arr[MAX], ans;
char binary[32];

struct Trie {
    Trie *next[2];

    Trie() {
        memset(next, 0, sizeof(next));
    }

    ~Trie() {
        for (int i = 0; i < 2; i++)
            if (next[i])
                delete next[i];
    }

    void insert(char *k) {
        if (*k == '\0')
            return;
        int nextIdx = *k - '0';
        if (!next[nextIdx])
            next[nextIdx] = new Trie();
        next[nextIdx]->insert(k + 1);
    }

    void query(char *k) {
        if (*k == '\0')
            return;
        int nextIdx = *k - '0';
        nextIdx ^= 1;
        if (!next[nextIdx]) {
            *k = '0';
            return next[nextIdx ^ 1]->query(k + 1);
        } else {
            *k = '1';
            return next[nextIdx]->query(k + 1);
        }
    }
};

void IntegerToBinary(int x) {
    for (int i = 30; i >= 0; i--) {
        if (x % 2)
            binary[i] = '1';
        else
            binary[i] = '0';
        x /= 2;
    }
    binary[31] = '\0';
    return;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    Trie *root = new Trie();
    for (int i = 0; i < N; i++)
        cin >> arr[i];
    for (int i = 0; i < N; i++) {
        memset(binary, 0, sizeof(binary));
        IntegerToBinary(arr[i]);
        root->insert(binary);
    }
    for (int i = 0; i < N; i++) {
        memset(binary, 0, sizeof(binary));
        IntegerToBinary(arr[i]);
        root->query(binary);
        int tmp = 0;
        for (int j = 30; j >= 0; j--)
            tmp += (binary[j] - '0') * pow(2, 30 - j);
        ans = max(ans, tmp);
    }
    cout << ans << '\n';
    return 0;
}