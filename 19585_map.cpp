#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;
typedef long long ll;
typedef pair<int, int> pi;
typedef pair<ll, ll> pl;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<ll> vl;
typedef vector<vl> vvl;
#define fastio ios_base::sync_with_stdio(0);cin.tie(NULL);
#define endl "\n"
#define pb push_back
#define all(X) begin((X)), end((X))
#define sz(X) (int)(X).size()
#define fi first
#define se second
#define fv(X) for(auto&_:(X))cin>>_
#define fv2(X) for(auto&_1:(X))for(auto&_2:_1)cin>>_2
unordered_set<string> nickname;

class TrieColor {
private:
    const static int child_cnt = 26;
    const static char first_child = 'a';
public:
    bool has_value = false;
    TrieColor *child[child_cnt];

    TrieColor() {
        for (int i = 0; i < child_cnt; i++)
            child[i] = 0;
    }

    ~TrieColor() {
        for (int i = 0; i < child_cnt; i++)
            delete child[i];
    }

    void insert(char *s) {
        if (s[0] == '\0') {
            has_value = true;
            return;
        }

        int idx = s[0] - first_child;

        if (!child[idx]) {
            child[idx] = new TrieColor();
        }
        child[idx]->insert(s + 1);
    }

    bool find(char *s) {
        if (s[0] == '\0')
            return false;

        if (has_value) {
            if (nickname.find(s) != nickname.end())
                return true;
        }

        int idx = s[0] - first_child;

        if (!child[idx])
            return false;
        return child[idx]->find(s + 1);
    }
};

TrieColor color;

void solve() {
    string s;
    int C, N, Q;
    cin >> C >> N;
    for (int i = 0; i < C; i++) {
        cin >> s;
        color.insert(&s[0]);
    }
    for (int i = 0; i < N; i++) {
        cin >> s;
        nickname.insert(&s[0]);
    }
    cin >> Q;
    while (Q--) {
        cin >> s;
        if (color.find(&s[0]))
            cout << "Yes\n";
        else
            cout << "No\n";

    }
}

int main() {
    fastio
    solve();
    return 0;
}