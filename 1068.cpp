/*
#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

int N, tmp, cnt, E;
vector<vector<int>> tree;
bool exist[51];

void dfs(int root) {
    exist[root] = false;
    for (int i = 0; i < tree[root].size(); i++) {
        int next = tree[root][i];
        if (!exist[next]) continue;
        exist[next] = false;
        dfs(next);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> N;
    tree.resize(N);
    memset(exist, true, sizeof(exist));
    for (int i = 0; i < N; i++) {
        cin >> tmp;
        if (tmp == -1) continue;
        tree[tmp].push_back(i);
    }
    cin >> E;
    dfs(E);

    for (int i = 0; i < N; i++) {
        vector<int>::iterator it = tree[i].begin();
        for (int j = 0; j < tree[i].size(); j++) {
            if (tree[i][j] == E) {
                it = tree[i].erase(it);
                break;
            }
            it++;
        }
    }

    for (int i = 0; i < N; i++)
        if (exist[i] && tree[i].size() == 0)
            cnt++;
    cout << cnt << '\n';
    return 0;
}*/

#include <iostream>
#include <vector>

using namespace std;

int cnt;

class Node {
public:
    int data;
    Node *par;
    vector<Node *> child;

    Node() {
        data = 0;
        par = NULL;
    }
};

class Tree {
public:
    Node *root;
    vector<Node *> list;

    Tree() {
        root = NULL;
    }

    Node *findNode(int e) {
        for (int i = 0; i < list.size(); i++) {
            if (list[i]->data == e) {
                return list[i];
            }
        }
        return NULL;
    }

    void insertRoot() {
        Node *new_node = new Node();
        new_node->data = 0;
        root = new_node;
        list.push_back(new_node);
    }

    void insertNode(int p, int c) {
        if (p == -1) {
            insertRoot();
        } else {
            Node *par_node = findNode(p);

            Node *new_node = new Node();
            new_node->data = c;
            new_node->par = par_node;
            par_node->child.push_back(new_node);
            list.push_back(new_node);
        }
    }

    void delChild(Node *v) {
        for (int i = 0; i < list.size(); i++) {
            for (int j = 0; j < list[i]->child.size(); j++) {
                if (list[i]->child[j] == v) {
                    list[i]->child[j]->par = NULL;
                    list[i]->child[j] = NULL;
                }
            }
        }
    }

    void del(Node *v) {
        v->data = -1;
        for (int i = 0; i < v->child.size(); i++) {
            v->child[i]->par = NULL;
            v->child[i] = NULL;
        }
        v = NULL;
        return;
    }

    void eraseNode(int e) {
        if (e == 0) {
            return;
        } else {
            Node *del_node = findNode(e);
            if (del_node == NULL) return;
            del(del_node);
            delChild(del_node);
        }
    }

    int countChild(Node *v) {
        if (v == NULL) return 0;
        int count_child = 0;
        for (int i = 0; i < v->child.size(); i++)
            if (v->child[i] != NULL)
                count_child++;
        return count_child;
    }

    void leafCount(Node *v) {
        for (int i = 0; i < list.size(); i++) {
            int count_child= countChild(list[i]);
            if (count_child == 0 && list[i]->data != -1)
                cnt++;
        }
    }

};

int main() {

    int N;
    cin >> N;
    Tree tree;

    for (int i = 0; i < N; i++) {
        int x;
        cin >> x;
        tree.insertNode(x, i);
    }

    int del;
    cin >> del;

    if (del == 0)
        cout << 0 << endl;
    else {
        tree.eraseNode(del);
        tree.leafCount(tree.root);
        cout << cnt << endl;
    }
    return 0;
}