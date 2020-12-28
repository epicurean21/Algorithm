#include <iostream>
#include <string>
#include <queue>
using namespace std;

string num;
int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};
queue<pair<string,int>> q;
void bfs(string str) {
    q.push({str, 0});
    
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int tmp;
            cin >> tmp;
            if(!tmp)
                num += '9';
            else
                num += (tmp + '0');
        }
    }

    return 0;
}