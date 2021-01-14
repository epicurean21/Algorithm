#include <iostream>
#include <vector>

using namespace std;

int N;
vector<vector<char>> tree;

void preorder(char node) {
    if(node == '.')
         return;

    cout << node;
    preorder(tree[node - 'A'][0]);
    preorder(tree[node - 'A'][1]);
}

void inorder(char node) {
    if(node == '.')
        return;
    inorder(tree[node - 'A'][0]);
    cout << node;
    inorder(tree[node - 'A'][1]);
}

void postorder(char node) {
    if(node == '.')
        return;
    postorder(tree[node - 'A'][0]);
    postorder(tree[node - 'A'][1]);
    cout << node;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N;
    tree.resize(N + 1);
    for (int i = 1; i <= N; i++) {
        char a, b, c;
        cin >> a >> b >> c;
        tree[a - 'A'].push_back(b);
        tree[a - 'A'].push_back(c);
    }
    preorder('A');
    cout << "\n";
    inorder('A');
    cout << "\n";
    postorder('A');
    cout << "\n";
    return 0;
}