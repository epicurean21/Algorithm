/**
 * 13936 나3곱2
 */
#include <iostream>
#include <vector>

using namespace std;
int N, a;

class A {
public:
    int value;
    A *pre;
    A *next;

    A() {}

    A(int v, A *p, A *n) {
        this->value = v;
        this->pre = p;
        this->next = n;
    }
};

bool Na3(int x, int y) {
    return x / 3 == y;
}

bool Gob2(int x, int y) {
    return x * 2 == y;
}

vector<A *> A_vector;
A *start;

void solve(A *aa) {
    cout << aa->value << " ";
    if (aa->next != nullptr)
        solve(aa->next);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    for (int i = 0; i < N; i++) {
        cin >> a;
        A *value = new A(a, nullptr, nullptr);
        A_vector.emplace_back(value);
    }
    for (int i = 0; i < N; i++) {
        int cur = A_vector[i]->value;
        for (int j = 0; j < N; j++) {
            if (i == j) continue;
            int value = A_vector[j]->value;
            if (cur % 3 == 0 && Na3(cur, value)) {
                A_vector[i]->next = A_vector[j];
                A_vector[j]->pre = A_vector[i];
            } else if (value % 3 == 0 && Na3(value, cur)) {
                A_vector[j]->next = A_vector[i];
                A_vector[i]->pre = A_vector[j];
            } else if (Gob2(cur, value)) {
                A_vector[i]->next = A_vector[j];
                A_vector[j]->pre = A_vector[i];
            } else if (Gob2(value, cur)) {
                A_vector[j]->next = A_vector[i];
                A_vector[i]->pre = A_vector[j];
            }
        }

        if (A_vector[i]->pre == nullptr)
            start = A_vector[i];
    }
    solve(start);

    return 0;
}