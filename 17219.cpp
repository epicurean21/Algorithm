/**
 * 17219 비밀번호 찾기
 * map
 */
#include <iostream>
#include <unordered_map>

using namespace std;
int N, M;
string url, password;
unordered_map<string, string> sites;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;
    while (N--) {
        cin >> url >> password;
        sites[url] = password;
    }
    while (M--) {
        cin >> url;
        cout << sites[url] << "\n";
    }
    return 0;
}