/**
 * 1302 베스트셀러
 * map
 */
#include <iostream>
#include <map>
#include <algorithm>

using namespace std;
int N, cnt;
string book, ans;
map<string, int> books;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;
    while (N--) {
        cin >> book;
        books[book]++;
    }
    for (auto b: books) {
        if (b.second > cnt) {
            cnt = b.second;
            ans = b.first;
        }
    }
    cout << ans << "\n";
    return 0;
}