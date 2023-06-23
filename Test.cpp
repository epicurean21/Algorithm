/**
 * 2820 자동차 공장
 * 자료구조, 세그먼트 트리, Lazy Propagation
 *
 */

#include "iostream"
#include "cmath"
#include "vector"

using namespace std;
int n, m;
vector<int> segment_tree, lazy_propagation_tree, ;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    cin >> n >> m;
    int h = (int) ceil(log2(n + 1));
    segment_tree.resize(1 << (h + 1));
    lazy_propagation_tree.resize(1 << (h + 1));

    for (int i = 0; i < n; i++) {

    }
    return 0;
}